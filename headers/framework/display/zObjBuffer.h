#pragma once

#include <depends/openGL/glew.h>
#include <depends/openGL/glext.h>

#include <GL/GL.h>			// Header File For The OpenGL32 Library
#include <gl/glu.h>			// Header File For The GLu32 Library

#include <windows.h>		// Header File For Windows

#include <headers/framework/core/zDefinitions.h>
#include <headers/framework/core/zVector.h>
#include <headers/framework/core/zColor.h>


namespace zSpace
{
	/** \addtogroup Framework
	*	\brief The datastructures of the library.
	*  @{
	*/

	/** \addtogroup zDisplay
	*	\brief  The display classes of the library.
	*  @{
	*/

	/*! \class zObjBuffer
	*	\brief A vertex buffer object class used to append geometry to the buffer.
	*	\since version 0.0.1
	*/

	/** @}*/

	/** @}*/

	class  zObjBuffer
	{
	public:

		//--------------------------
		//----  ATTRIBUTES
		//--------------------------

		/*!	\brief VBO for vertices - positions and normals(if available)  */
		GLuint VBO_vertices;

		/*!	\brief VBO for vertex color  */
		GLuint VBO_vertexColors;

		/*!	\brief VBO to store edge vertex connectivity indicies  */
		GLuint VBO_edgeIndices;

		/*!	\brief VBO to store face vertex connectivity indicies  */
		GLuint VBO_faceIndices;

		/*!	\brief stores number of max vertices possible in the buffer  */
		GLint max_nVertices;

		/*!	\brief stores number of vertices in the buffer  */
		GLint nVertices;

		/*!	\brief stores number of colors in the buffer  */
		GLint nColors;

		/*!	\brief stores number of edge vertex connectivity indicies in the buffer  */
		GLint nEdges;

		/*!	\brief stores number of edge vertex connectivity indicies in the buffer  */
		GLint nFaces;

		

		//--------------------------
		//----  CONSTRUCTOR
		//--------------------------

		/*! \brief Default constructor.
		*
		*	\since version 0.0.1
		*/
		
		zObjBuffer()
		{

			nVertices = 0;
			nColors = 0;
			nEdges = 0;
			nFaces = 0;

			max_nVertices = 0;

		}


		/*! \brief Overloaded constructor.
		*
		*	\param		[in]	_Max_Num_Verts		- size of the buffer to be initialised.
		*	\since version 0.0.1
		*/

		zObjBuffer(GLint _Max_Num_Verts)
		{
			nVertices = 0;
			nColors = 0;
			nEdges = 0;
			nFaces = 0;

			max_nVertices = _Max_Num_Verts;

			GLfloat *vertices = new GLfloat[max_nVertices * vertexAttribStride];
			GLfloat *colors = new GLfloat[max_nVertices * vertexColorStride];

			GLint *edgeIndicies = new GLint[max_nVertices * 2 * edgeIndexStride];
			GLint *faceIndicies = new GLint[max_nVertices * 2 * faceIndexStride];

			GLsizei max_size_Vertices = max_nVertices * vertexAttribStride * GLFloatSize;
			GLsizei max_size_Colors = max_nVertices * vertexColorStride *  GLFloatSize;
			GLsizei max_size_Edgeindicies = max_nVertices * 2 * edgeIndexStride *  GLIntSize;
			GLsizei max_size_Faceindicies = max_nVertices * 2 * faceIndexStride *  GLIntSize;

			glGenBuffers(1, &VBO_vertices);
			glBindBuffer(GL_ARRAY_BUFFER, VBO_vertices);
			glBufferData(GL_ARRAY_BUFFER, max_size_Vertices, vertices, GL_STREAM_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0); //  source a standard memory location(RAM)

			glGenBuffers(1, &VBO_vertexColors);
			glBindBuffer(GL_ARRAY_BUFFER, VBO_vertexColors);
			glBufferData(GL_ARRAY_BUFFER, max_size_Colors, colors, GL_STREAM_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			glGenBuffers(1, &VBO_edgeIndices);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO_edgeIndices);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, max_size_Edgeindicies, edgeIndicies, GL_STREAM_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

			glGenBuffers(1, &VBO_faceIndices);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO_faceIndices);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, max_size_Faceindicies, faceIndicies, GL_STREAM_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

			delete[] vertices;
			delete[] colors;

			delete[] edgeIndicies;
			delete[] faceIndicies;

		}

		//--------------------------
		//----  DESSTRUCTOR
		//--------------------------

		/*! \brief Default destructor.
		*
		*	\since version 0.0.1
		*/

		~zObjBuffer(){}

		//--------------------------
		//----  APPEND METHODS
		//--------------------------


		/*! \brief This method appends the vertex attributes of position and normals(if available) to the buffer. 
		*
		*	\param		[in]	_positions			- zVector pointer to vertex positions container.
		*	\param		[in]	_normals			- zVector pointer to vertex normals container.
		*	\param		[in]	size				- size of container.
		*	\since version 0.0.1
		*/
		int appendVertexAttributes(zVector*_positions, zVector* _normals, int size)
		{

			int out = nVertices;

			GLfloat *vertices = new GLfloat[size * vertexAttribStride];

			for (int i = 0; i < size; i++)
			{
				vertices[(i * vertexAttribStride) + 0] = _positions[i].x;
				vertices[(i * vertexAttribStride) + 1] = _positions[i].y;
				vertices[(i * vertexAttribStride) + 2] = _positions[i].z;


				if (!_normals)
				{
					vertices[(i * vertexAttribStride) + 3] = _normals[i].x;
					vertices[(i * vertexAttribStride) + 4] = _normals[i].y;
					vertices[(i * vertexAttribStride) + 5] = _normals[i].z;
				}
			}

			glBindBuffer(GL_ARRAY_BUFFER, VBO_vertices);
			glBufferSubData(GL_ARRAY_BUFFER, nVertices * vertexAttribStride * GLFloatSize, size  * vertexAttribStride * GLFloatSize, vertices);

			nVertices += size;

			delete[] vertices;

			return out;
		}

		/*! \brief This method appends the vertex color attribute to the buffer.
		*
		*	\param		[in]	_colors				- zColor pointer to vertex colors container.
		*	\param		[in]	size				- size of container.
		*	\since version 0.0.1
		*/
		int appendVertexColors(zColor* _colors, int size)
		{

			int out = nColors;

			GLfloat *colors = new GLfloat[size * vertexColorStride];

			for (int i = 0; i < size; i++)
			{
				colors[(i * vertexColorStride) + 0] = _colors[i].r;
				colors[(i * vertexColorStride) + 1] = _colors[i].g;
				colors[(i * vertexColorStride) + 2] = _colors[i].b;
				colors[(i * vertexColorStride) + 3] = _colors[i].a;
			}


			glBindBuffer(GL_ARRAY_BUFFER, VBO_vertexColors);
			glBufferSubData(GL_ARRAY_BUFFER, nColors * vertexColorStride *GLFloatSize, size * vertexColorStride * GLFloatSize, colors);

			nColors += size;

			delete[] colors;

			return out;

		}

		/*! \brief This method appends the edge vertex connectivity indicies to the buffer.
		*
		*	\param		[in]	_edgeIndicies			- container of edge vertex connectivity indicies.
		*	\since version 0.0.1
		*/
		int appendEdgeIndices(vector<int> &_edgeIndicies)
		{
			int out = nEdges;

			GLint *edgeIndicies = new GLint[_edgeIndicies.size() * edgeIndexStride];

			for (int i = 0; i < _edgeIndicies.size(); i++)
			{
				edgeIndicies[i] = _edgeIndicies[i];
			}


			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO_edgeIndices);
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, nEdges * edgeIndexStride *GLIntSize, _edgeIndicies.size() * edgeIndexStride * GLIntSize, edgeIndicies);

			nEdges += _edgeIndicies.size();


			delete[] edgeIndicies;

			return out;
		}

		/*! \brief This method appends the face vertex connectivity indicies to the buffer.
		*
		*	\param		[in]	_faceIndicies			- container of face vertex connectivity indicies.
		*	\since version 0.0.1
		*/
		int appendFaceIndices(vector<int> &_faceIndicies)
		{
			int out = nFaces;

			GLint *faceIndicies = new GLint[_faceIndicies.size() * faceIndexStride];

			for (int i = 0; i < _faceIndicies.size(); i++)
			{
				faceIndicies[i] = _faceIndicies[i];
			}


			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO_faceIndices);
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, nFaces * faceIndexStride *GLIntSize, _faceIndicies.size() * faceIndexStride * GLIntSize, faceIndicies);

			nFaces += _faceIndicies.size();


			delete[] faceIndicies;

			return out;
		}
			
			   
		//--------------------------
		//----  UPDATE METHODS
		//--------------------------

		
		/*! \brief This method update the vertex positions stored in the buffer from the buffer offset given by the input start index.
		*
		*	\param		[in]	_positions			- zVector pointer to vertex positions container.
		*	\param		[in]	size				- size of container.
		*	\param		[in]	startId				- buffer offset.
		*	\since version 0.0.1
		*/
		void updateVertexPositions(zVector* _positions, int size,  int startId)
		{

			GLfloat *positions = new GLfloat[size * vertexAttribStride];			

			for (int i = 0; i < size; i++)
			{
				positions[(i * vertexAttribStride) + 0] = _positions[i].x;
				positions[(i * vertexAttribStride) + 1] = _positions[i].y;
				positions[(i * vertexAttribStride) + 2] = _positions[i].z;
			}

			glBindBuffer(GL_ARRAY_BUFFER, VBO_vertices);
			glBufferSubData(GL_ARRAY_BUFFER, startId * vertexAttribStride * GLFloatSize, size  * vertexAttribStride * GLFloatSize, positions);

			delete[] positions;

		}

		/*! \brief This method update the vertex normals stored in the buffer from the buffer offset given by the input start index.
		*
		*	\param		[in]	_normals			-  zVector pointer to vertex normals container.
		*	\param		[in]	size				- size of container.
		*	\param		[in]	startId				- buffer offset.
		*	\since version 0.0.1
		*/
		
		void updateVertexNormals(zVector* _normals, int size, int &startId)
		{
			GLfloat *normals = new GLfloat[size * vertexAttribStride];

			for (int i = 0; i < size; i++)
			{
				normals[(i * vertexAttribStride) + 3] = _normals[i].x;
				normals[(i * vertexAttribStride) + 4] = _normals[i].y;
				normals[(i * vertexAttribStride) + 5] = _normals[i].z;
			}

			glBindBuffer(GL_ARRAY_BUFFER, VBO_vertices);
			glBufferSubData(GL_ARRAY_BUFFER, startId * vertexAttribStride * GLFloatSize, size  * vertexAttribStride * GLFloatSize, normals);

			delete[] normals;

		}

		/*! \brief This method update the vertex colors stored in the buffer from the buffer offset given by the input start index.
		*
		*	\param		[in]	_colors				- zColor pointer to vertex colors container.
		*	\param		[in]	size				- size of container.
		*	\param		[in]	startId				- buffer offset.
		*	\since version 0.0.1
		*/

		void updateVertexColors(zColor*_colors, int size, int &startId)
		{
			GLfloat *colors = new GLfloat[size * vertexColorStride];

			for (int i = 0; i < size; i++)
			{
				colors[(i * vertexColorStride) + 0] = _colors[i].r;
				colors[(i * vertexColorStride) + 1] = _colors[i].g;
				colors[(i * vertexColorStride) + 2] = _colors[i].b;
				colors[(i * vertexColorStride) + 3] = _colors[i].a;
			}


			glBindBuffer(GL_ARRAY_BUFFER, VBO_vertexColors);
			glBufferSubData(GL_ARRAY_BUFFER, startId * vertexColorStride *GLFloatSize, size * vertexColorStride * GLFloatSize, colors);

			delete[] colors;

		}


		//--------------------------
		//----  CLEAR METHODS
		//--------------------------
	
		/*! \brief This method clears all the buffer for rewriting.
		*
		*	\since version 0.0.1
		*/

		void clearBufferForRewrite()
		{
			nVertices = nColors = nEdges = nFaces = 0;

		}

	};
}