// This file is part of zspace, a simple C++ collection of geometry data-structures & algorithms, 
// data analysis & visualization framework.
//
// Copyright (C) 2019 ZSPACE 
// 
// This Source Code Form is subject to the terms of the MIT License 
// If a copy of the MIT License was not distributed with this file, You can 
// obtain one at https://opensource.org/licenses/MIT.
//
// Author : Vishu Bhooshan <vishu.bhooshan@zaha-hadid.com>
//


#include<headers/zHousing/architecture/zHcStructure.h>
#include <headers/zHousing/architecture/zHcUnit.h>



namespace zSpace
{
	//---- CONSTRUCTOR

	ZSPACE_INLINE zHcStructure::zHcStructure() {}


		/*! \brief container to cell faces attributes */
	ZSPACE_INLINE zHcStructure::zHcStructure(zObjMesh&_inMeshObj, zPointArray &faceVertexPositions, zObjMeshPointerArray&_columnObjs, zObjMeshPointerArray&_slabObjs, zObjMeshPointerArray&_wallObjs, zObjMeshPointerArray&_facadeObjs, zBoolArray&_cellEdgesAttributes, zBoolArray&_cellBoundaryAttributes, zFunctionType&_funcType)
	{
		inMeshObj = &_inMeshObj;
		fnInMesh = zFnMesh(_inMeshObj);	

		columnObjs = _columnObjs;
		slabObjs = _slabObjs;
		wallObjs = _wallObjs;
		facadeObjs = _facadeObjs;

		cellEdgesAttributes = _cellEdgesAttributes;
		cellBoundaryAttributes = _cellBoundaryAttributes;

		createStructureCell(faceVertexPositions);
		setCellFacesAttibutes();

		if (_funcType == zFunctionType::zPublic)
		{
			createColumns();
			createSlabs();
		}
		else
		{
			createWalls();
			createFacades();
		}
	}

	//---- DESTRUCTOR

	ZSPACE_INLINE zHcStructure::~zHcStructure() {}

	//---- SET METHODS
	   	 

	void zHcStructure::createStructureCell(zPointArray &vPositions)
	{
		zIntArray polyConnect;
		zIntArray polyCount;

		int vPositionsCount = vPositions.size();
		polyCount.push_back(vPositions.size());

		for (int i = 0; i < vPositions.size(); i++)
		{
			polyConnect.push_back(i);
		}

		zObjMesh tempObj;
		zFnMesh tempFn(tempObj);

		tempFn.create(vPositions, polyCount, polyConnect);
		tempFn.extrudeMesh(-height, *inMeshObj, false);
	}

	void zHcStructure::setCellFacesAttibutes()
	{
		for (zItMeshFace f(*inMeshObj);  !f.end(); f++)
		{
			if (f.getId() == 0) cellFaceArray.push_back(zCellFace::zRoof);
			else if (f.getId() == 1) cellFaceArray.push_back(zCellFace::zFloor);
			else break;
		}

		for (int i = 0; i < cellBoundaryAttributes.size(); i++)
		{
			if (cellBoundaryAttributes[i] == true) cellFaceArray.push_back(zCellFace::zFacade);
			else cellFaceArray.push_back(zCellFace::zIntWall);
		}
	}

	bool zHcStructure::createColumns()
	{
		if (!inMeshObj) return false;

		zFnMesh tempfnMesh(*inMeshObj);

		for (zItMeshFace f(*inMeshObj); !f.end(); f++)
		{
			if (cellFaceArray[f.getId()] == zCellFace::zRoof)
			{
				zIntArray heIndices;
				f.getHalfEdges(heIndices);
				
				int heCount = 0;
				for (int i : heIndices)
				{
					zItMeshHalfEdge he(*inMeshObj, i);
					
					//set column position
					zVector columnPos = he.getStartVertex().getPosition();

					//set direction according to edge attributes
					zVector x, y;
					if (cellEdgesAttributes[heCount])
					{
						x = he.getVector();
						y = he.getPrev().getVector() * -1;
					}
					else
					{
						y = he.getVector();
						x = he.getPrev().getVector()* -1;
					}

					zVector z = zVector(0, 0, -1);

					zAgColumn tempColumn = zAgColumn(*columnObjs[heCount], columnPos, x, y, z, height);
					columnArray.push_back(tempColumn);

					heCount++;
				}
			}
		}
		
		return true;
	}

	bool zHcStructure::createSlabs()
	{
		if (!inMeshObj || columnArray.size() == 0) return false;

		zFnMesh tempfnMesh(*inMeshObj);

		for (zItMeshFace f(*inMeshObj); !f.end(); f++)
		{
			if (cellFaceArray[f.getId()] == zCellFace::zRoof)
			{
				zIntArray heIndices;
				f.getHalfEdges(heIndices);

				int heCount = 0;
				for (int i : heIndices)
				{
					zItMeshHalfEdge he(*inMeshObj, i);

					//set slab center
					zVector center = f.getCenter();

					//set xCenter and yCenter according to edge attributes
					zVector xCenter, yCenter;
					if (cellEdgesAttributes[heCount])
					{
						xCenter = he.getCenter();
						yCenter = he.getPrev().getCenter();
					}
					else
					{
						yCenter = he.getCenter();
						xCenter = he.getPrev().getCenter();
					}

					zAgSlab tempSlab = zAgSlab(*slabObjs[heCount], xCenter, yCenter, center, columnArray[heCount]);
					slabArray.push_back(tempSlab);

					heCount++;
				}

			}
		}


		return true;
	}

	bool zHcStructure::createWalls()
	{
		if (!inMeshObj) return false;

		int count = 0;
		for (zItMeshFace f(*inMeshObj); !f.end(); f++)
		{
			if (cellFaceArray[f.getId()] == zCellFace::zIntWall)
			{
				zPointArray vCorners;
				f.getVertexPositions(vCorners);

				zAgWall tempWall = zAgWall(*wallObjs[count], vCorners);

				count++;
			}
		}

		printf("\n num of walls placed: %i", count);

		return true;
	}

	bool zHcStructure::createFacades()
	{
		if (!inMeshObj) return false;


		return true;
	}

	

}