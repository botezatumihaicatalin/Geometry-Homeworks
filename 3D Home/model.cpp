#include "model.h"
#include <sstream>
#include <fstream>
#include <iostream>

vector<string> & split(const string &s, char delim, vector<string> &elems) {
	stringstream ss(s);
	string item;
	while (getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

vector<string> split(const string &s, char delim) {
	vector<string> elems;
	split(s, delim, elems);
	return elems;
}

ObjObject::~ObjObject() {
	if (_listId == 0) {
		return;
	}
	glDeleteLists(_listId, 1);
	_listId = 0;
}

bool ObjModel::_processMtlLine(const string & line) {

	vector<string> splittedLine = split(line, ' ');
	static string lastMaterialDefined = "";

	int splittedLineSize = splittedLine.size();

	if (splittedLineSize == 0) {
		return true;
	}

	if (splittedLine[0] == "#") {
		return true;
	}

	if (splittedLine[0] == "newmtl" && splittedLineSize >= 2) {

		string materialName = "";

		for (unsigned int index = 1; index < splittedLine.size(); index++) {
			materialName += splittedLine[index];
		}

		lastMaterialDefined = materialName;
		Materials[materialName] = ObjMaterial(lastMaterialDefined);
		return true;
	}

	if (splittedLine[0] == "Ka" && splittedLineSize >= 4) {

		auto materialIt = Materials.find(lastMaterialDefined);
		if (materialIt == Materials.end()) {
			return false;
		}

		ObjMaterial & materialRef = materialIt->second;
		materialRef.AmbientRGB[0] = atof(splittedLine[1].c_str());
		materialRef.AmbientRGB[1] = atof(splittedLine[2].c_str());
		materialRef.AmbientRGB[2] = atof(splittedLine[3].c_str());
		return true;
	}

	if (splittedLine[0] == "Kd" && splittedLineSize >= 4) {

		auto materialIt = Materials.find(lastMaterialDefined);
		if (materialIt == Materials.end()) {
			return false;
		}

		ObjMaterial & materialRef = materialIt->second;
		materialRef.DiffuseRGB[0] = atof(splittedLine[1].c_str());
		materialRef.DiffuseRGB[1] = atof(splittedLine[2].c_str());
		materialRef.DiffuseRGB[2] = atof(splittedLine[3].c_str());
		return true;
	}

	if (splittedLine[0] == "Ks" && splittedLineSize >= 4) {

		auto materialIt = Materials.find(lastMaterialDefined);
		if (materialIt == Materials.end()) {
			return false;
		}

		ObjMaterial & materialRef = materialIt->second;
		materialRef.SpecularRGB[0] = atof(splittedLine[1].c_str());
		materialRef.SpecularRGB[1] = atof(splittedLine[2].c_str());
		materialRef.SpecularRGB[2] = atof(splittedLine[3].c_str());
		return true;
	}

	if (splittedLine[0] == "Ns" && splittedLineSize >= 2) {

		auto materialIt = Materials.find(lastMaterialDefined);
		if (materialIt == Materials.end()) {
			return false;
		}

		ObjMaterial & materialRef = materialIt->second;
		materialRef.SpecularExponent = atof(splittedLine[1].c_str());
		return true;
	}

	if ((splittedLine[0] == "d" || splittedLine[0] == "Tr")
			&& splittedLineSize >= 2) {

		auto materialIt = Materials.find(lastMaterialDefined);
		if (materialIt == Materials.end()) {
			return false;
		}

		ObjMaterial & materialRef = materialIt->second;
		materialRef.Transparency = atof(splittedLine[1].c_str());
		return true;
	}

	if (splittedLine[0] == "illum" && splittedLineSize >= 2) {
		auto materialIt = Materials.find(lastMaterialDefined);
		if (materialIt == Materials.end()) {
			return false;
		}

		ObjMaterial & materialRef = materialIt->second;
		materialRef.Illumination = atoi(splittedLine[1].c_str());
		return true;
	}

	if (splittedLine[0] == "Ni") {
		return true;
	}

	return false;
}

bool ObjModel::_processObjLine(const string & line) {

	static string lastMaterialUsed = "";

	vector<string> splittedLine = split(line, ' ');

	int splittedLineSize = splittedLine.size();

	if (splittedLineSize == 0) {
		return false;
	}

	if (splittedLine[0] == "#") {
		return true;
	}

	if (splittedLine[0] == "v" && splittedLineSize >= 4) {
		ObjVertex vertex;
		vertex.X = atof(splittedLine[1].c_str());
		vertex.Y = atof(splittedLine[2].c_str());
		vertex.Z = atof(splittedLine[3].c_str());
		Vertices.push_back(vertex);
		return true;
	}

	if (splittedLine[0] == "vt" && splittedLineSize >= 3) {
		ObjTexture texture;
		texture.X = atof(splittedLine[1].c_str());
		texture.Y = atof(splittedLine[2].c_str());
		Textures.push_back(texture);
		return true;
	}

	if (splittedLine[0] == "vn" && splittedLineSize >= 4) {
		ObjNormal normal;
		normal.X = atof(splittedLine[1].c_str());
		normal.Y = atof(splittedLine[2].c_str());
		normal.Z = atof(splittedLine[3].c_str());
		Normals.push_back(normal);
		return true;
	}

	if (splittedLine[0] == "f") {

		if (Objects.empty()) {
			Objects.push_back(ObjObject("Untitled"));
		}

		ObjFace newFace(lastMaterialUsed);

		for (unsigned int index = 1; index < splittedLine.size(); index++) {

			ObjFaceItem faceItem;

			if (sscanf(splittedLine[index].c_str(), "%d", &faceItem.VertexIndex)
					== 1) {
				faceItem.VertexIndex--;
			} else if (sscanf(splittedLine[index].c_str(), "%d/%d",
					&faceItem.VertexIndex, &faceItem.TextureIndex) == 2) {
				faceItem.VertexIndex--;
				faceItem.TextureIndex--;
			} else if (sscanf(splittedLine[index].c_str(), "%d/%d/%d",
					&faceItem.VertexIndex, &faceItem.TextureIndex,
					&faceItem.NormalIndex) == 3) {
				faceItem.VertexIndex--;
				faceItem.TextureIndex--;
				faceItem.NormalIndex--;
			} else if (sscanf(splittedLine[index].c_str(), "%d//%d",
					&faceItem.VertexIndex, &faceItem.NormalIndex) == 2) {
				faceItem.VertexIndex--;
				faceItem.NormalIndex--;
			} else {
				return false;
			}
			newFace.FaceItems.push_back(faceItem);
		}

		Objects.back().Faces.push_back(newFace);
		return true;
	}

	if (splittedLine[0] == "o" && splittedLineSize >= 2) {

		string objectName = "";

		for (unsigned int index = 1; index < splittedLine.size(); index++) {
			objectName += splittedLine[index];
		}

		Objects.push_back(objectName);
		return true;
	}

	if (splittedLine[0] == "usemtl" && splittedLineSize >= 2) {

		string materialName = "";

		for (unsigned int index = 1; index < splittedLine.size(); index++) {
			materialName += splittedLine[index];
		}

		lastMaterialUsed = materialName;
		return true;
	}

	if (splittedLine[0] == "g") {
		// TODO : maybe handle groups?
		return true;
	}

	if (splittedLine[0] == "s") {
		// TODO : maybe handle smoothness (not necesary)
		return true;
	}

	if (splittedLine[0] == "mtllib") {
		// No need to handle this, we can give the paths manually to the material
		// files.
		return true;
	}

	return false;
}

bool ObjModel::Load(const string & dataPath, const string & objFilePath,
		const string & materialFilePath) {

	std::ifstream objFileStream(objFilePath);
	std::ifstream materialFileStream(materialFilePath);

	if (!objFileStream.is_open() || !materialFileStream.is_open()) {
		return false;
	}

	string line;

	for (; getline(materialFileStream, line);) {
		if (!_processMtlLine(line)) {
			return false;
		}
	}

	for (; getline(objFileStream, line);) {
		if (!_processObjLine(line)) {
			return false;
		}
	}

	for (unsigned int index = 0; index < Objects.size(); index++) {
		BuildObject(index);
	}

	return true;

}

void ObjModel::BuildObject(int objectIndex) {
	if (objectIndex < 0 || objectIndex >= Objects.size()) {
		return;
	}

	ObjObject & refObject = Objects[objectIndex];

	if (refObject._listId == 0) {
		refObject._listId = glGenLists(1);
	}

	glNewList(refObject._listId, GL_COMPILE);

	glEnable( GL_NORMALIZE);
	glEnable( GL_TEXTURE_2D);

	glColor3d(0, 0, 1);

	for (auto & face : refObject.Faces) {
		glBegin(GL_POLYGON);

		auto materialIt = Materials.find(face.MaterialName);

		if (materialIt != Materials.end()) {
			glMaterialfv( GL_FRONT, GL_AMBIENT, materialIt->second.AmbientRGB);
			glMaterialfv( GL_FRONT, GL_DIFFUSE, materialIt->second.DiffuseRGB);
			glMaterialfv( GL_FRONT, GL_SPECULAR, materialIt->second.SpecularRGB);
		}

		glShadeModel(GL_SMOOTH);

		for (auto & faceItem : face.FaceItems) {
			if (faceItem.NormalIndex != -1) {
				Vertex3 & refNormal = Normals[faceItem.NormalIndex];
				glNormal3d(refNormal.X, refNormal.Y, refNormal.Z);
			}

			Vertex3 & refVertice = Vertices[faceItem.VertexIndex];
			glVertex3d(refVertice.X, refVertice.Y, refVertice.Z);
		}

		glEnd();
	}

	glDisable( GL_NORMALIZE);
	glDisable( GL_TEXTURE_2D);

	glEndList();
}

void ObjModel::RenderObject(int objectIndex) {
	if (objectIndex < 0 || objectIndex >= Objects.size()) {
		return;
	}

	ObjObject & refObject = Objects[objectIndex];

	if (refObject._listId == 0) {
		return;
	}
	glCallList(refObject._listId);
}
