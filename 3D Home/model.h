/*
 * model.h
 *
 *  Created on: Jan 2, 2015
 *      Author: mihai
 */

#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <unordered_map>
#include <vector>
#include <GL/freeglut.h>
#include <map>

#include "vertex3.h"

using namespace std;

// Forward declaration of the classes

class ObjVertex;
class ObjNormal;
class ObjTexture;
class ObjFaceItem;
class ObjFace;
class ObjObject;
class ObjModel;


// Explicit declaration of the classes

class ObjVertex : public Vertex3 {
};

class ObjNormal : public Vertex3 {
};

class ObjTexture : public Vertex3 {
};

class ObjFaceItem {

public :
	ObjFaceItem(const int & vertexIndex = -1, const int & textureIndex = -1, const int & normalIndex = -1) :
		VertexIndex(vertexIndex), TextureIndex(textureIndex), NormalIndex(normalIndex) {}
	int VertexIndex , TextureIndex, NormalIndex;

};

class ObjFace {
public :
	ObjFace(const string & materialName = "") : MaterialName(materialName) {}
	vector <ObjFaceItem> FaceItems;
	string MaterialName;
};

class ObjMaterial {
public :
	ObjMaterial(const string & name = "") : Name(name), Transparency(1.0), Illumination(2), SpecularExponent(1.0) {
		AmbientRGB[0] = AmbientRGB[1] = AmbientRGB[2] = 1.0f;
		DiffuseRGB[0] = DiffuseRGB[1] = DiffuseRGB[2] = 1.0f;
		SpecularRGB[0] = SpecularRGB[1] = SpecularRGB[2] = 1.0f;
	}
	string Name;

	float AmbientRGB[3];
	float DiffuseRGB[3];
	float SpecularRGB[3];

	double Transparency;
	int Illumination;
	double SpecularExponent;
};

class ObjModel {

public :
	vector <ObjVertex> Vertices;
	vector <ObjNormal> Normals;
	vector <ObjTexture> Textures;
	vector <ObjObject> Objects;
	map <string, ObjMaterial> Materials;

	Vertex3 MinimumVertex;
	Vertex3 MaximumVertex;

	bool Load(const string & dataPath, const string & objFilePath, const string & materialFilePath);
	void BuildObject(int objectIndex);
	void RenderObject(int objectIndex);
	void ClearModelData();
	void RenderBoundingBox();

private:
	bool _processObjLine(const string & line);
	bool _processMtlLine(const string & line);

	string _lastObjectMaterialRead;
	string _lastMaterialNameRead;
};

class ObjObject {

public :
	ObjObject(const string & name = "") : Name(name) , _listId(0) {}
	virtual ~ObjObject();
	string Name;
	vector <ObjFace> Faces;
	friend void ObjModel::BuildObject(int objectIndex);
	friend void ObjModel::RenderObject(int objectIndex);
private:
	int _listId;

};



#endif /* MODEL_H_ */
