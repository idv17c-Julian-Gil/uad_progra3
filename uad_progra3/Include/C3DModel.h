#pragma once

#ifndef C3DMODEL_H
#define C3DMODEL_H

#include <string>
using namespace std;

class C3DModel
{
protected:
	unsigned int m_shaderProgramId;                                   // Shader program identifier generated by OpenGL
	unsigned int m_graphicsMemoryObjectId;                            // Vertex Array Object identifier generated by OpenGL
	unsigned int m_textureObjectId;									  // Texture object identifier generated by OpenGL

	unsigned short *m_vertexIndices;                                  // Dynamically-allocated array of vertex indices for this model
	unsigned short *m_normalIndices;                                  // Dynamically-allocated array of normal indices for this model
	unsigned short *m_UVindices;                                      // Dynamically-allocated array of UV coord indices for this model

	float *m_verticesRaw;                                             // Dynamically-allocated array of vertices (raw float values)
	float *m_normalsRaw;                                              // Dynamically-allocated array of normals (raw float values)
	float *m_uvCoordsRaw;                                             // Dynamically-allocated array of UV coords (raw float values)

	int m_numVertices, m_numNormals, m_numUVCoords, m_numFaces;       // Total number of vertices, normals, UV coords, and faces in this model

	bool m_Initialized;                                               // Does this C3DModel object contain valid data? (loaded from file)
	bool m_modelHasNormals;											  // Flag to determine if this model has normals
	bool m_modelHasUVs;												  // Flag to determine if this model has UVs
	bool m_modelHasTextures;										  // Flag to determine if this model has a valid texture filename
	char *m_modelTextureFilename;

	virtual void reset();                                             // Cleanup any allocated memory
	virtual bool loadFromFile(const char * const filename) = 0;

	void computeFaceNormals();                                        // If model didn't have any normals, compute face normals

public:
	C3DModel();
	virtual ~C3DModel();
	
	static C3DModel* load(const char * const filename);
	bool isInitialized() const { return m_Initialized; }
	void setInitialized(bool i) { m_Initialized = i; }

	unsigned int *getGraphicsMemoryObjectId() { return &m_graphicsMemoryObjectId; }
	void setGraphicsMemoryObjectId(unsigned int id) { m_graphicsMemoryObjectId = id; }

	unsigned int *getShaderProgramId() { return &m_shaderProgramId; }
	void setShaderProgramId(unsigned int id) { m_shaderProgramId = id; }

	unsigned int *getTextureObjectId() { return &m_textureObjectId; }
	void setTextureObjectId(unsigned int id) { m_textureObjectId = id; }

	int getNumVertices() const { return m_numVertices; }
	int getNumNormals() const { return m_numNormals; }
	int getNumUVCoords() const { return m_numUVCoords; }
	int getNumFaces() const { return m_numFaces; }
	float * const getModelVertices() { return m_verticesRaw; }
	float * const getModelNormals() { return m_normalsRaw; }
	float * const getModelUVCoords() { return m_uvCoordsRaw; }
	unsigned short * const getModelVertexIndices() { return m_vertexIndices; }
	unsigned short * const getModelNormalIndices() { return m_normalIndices; }
	unsigned short * const getModelUVCoordIndices() { return m_UVindices; }

	// Overloaded < operator. This is specifically used in the final exam to allow two 3D objects to be compared and decide on which side of the
	// binary tree it needs to be inserted.
	bool operator<(const C3DModel &other)
	{
		return (m_numFaces < other.m_numFaces);
	}
	// Overloaded > operator. This is specifically used in the final exam to allow two 3D objects to be compared and decide on which side of the
	// binary tree it needs to be inserted.
	bool operator>(const C3DModel &other)
	{
		return (m_numFaces > other.m_numFaces);
	}
	// Overloaded << operator. This is used in the final exam.
	friend ostream &operator<<(ostream &out, const C3DModel &model) {
		// Commented-out, this is rendered every frame...
		// out << "Num faces: " << model.getNumFaces() << endl;
		return out;
	}

	bool hasNormals() const { return m_modelHasNormals; }
	bool hasUVs() const { return m_modelHasUVs; }
	bool hasTextures() const { return m_modelHasTextures; }

	const char * const getTextureFilename() const { return m_modelTextureFilename; }
};

#endif // !C3DMODEL_H
