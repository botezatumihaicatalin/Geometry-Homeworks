/*
 * model.h
 *
 *  Created on: Jan 2, 2015
 *      Author: mihai
 */

#ifndef MODEL_H
#define MODEL_H

#include "vertex3.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <GL/freeglut.h>

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

class ObjModel {

public :
	vector <ObjVertex> Vertices;
	vector <ObjNormal> Normals;
	vector <ObjTexture> Textures;
	vector <ObjObject> Objects;
	bool Load(const string & dataPath, const string & objFilePath, const string & materialFilePath);
	void BuildObject(int objectIndex);
	void RenderObject(int objectIndex);

private:
	bool _processObjLine(const string & line);
	bool _processMtlLine(const string & line);
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
