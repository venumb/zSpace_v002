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

#ifndef ZSPACE_HC_UNIT_H
#define ZSPACE_HC_UNIT_H

#pragma once

#include <headers/zInterface/model/zModel.h>

#include <headers/zCore/base/zExtern.h>

#include <headers/zInterface/functionsets/zFnMesh.h>
#include <headers/zInterface/functionsets/zFnGraph.h>

#include <headers/zHousing/base/zHcEnumerators.h>
#include <headers/zHousing/base/zHcTypeDef.h>

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;


namespace zSpace
{

	/*! \class zHcUnit
	*	\brief A toolset for housing units configuration
	*	\since version 0.0.4
	*/

	/** @}*/

	class ZSPACE_AG zHcUnit
	{
	protected:
		//--------------------------
		//---- PROTECTED ATTRIBUTES
		//--------------------------

		/*!	\brief pointer to display model  */
		zModel *model;

	public:
		//--------------------------
		//---- PUBLIC ATTRIBUTES
		//--------------------------


		/*!	\brief pointer to input mesh Object  */
		zObjMesh *inUnitMeshObj;

		/*!	\brief input mesh function set  */
		zFnMesh fnUnitMesh;

		/*!	\brief pointer to input mesh Object  */
		zObjMeshArray layoutMeshObjs;

		/*!	\brief input mesh function set  */
		vector<zFnMesh> fnLayoutMeshArray;

		/*!	\brief house layout option */
		zLayoutType layoutType;

		/*!	\brief house function option */
		zFunctionType funcType;

		/*!	\brief house structure option */
		zStructureType structureType;

		/*!	\brief structure units/cells array */
		zHcStructure structureUnit;

		/*!	\brief store edge attributes: primary (true) secondary (false)  */
		zBoolArray edgeAttributes;

		/*!	\brief store boundary attributes */
		zBoolArray eBoundaryAttributes;

		/*!	\brief store structure height array */
		zFloatArray structureHeight;

		/*!	\brief interface manager, handles an input path directory*/
		zUtilsCore core;
		
		//--------------------------
		//---- CONSTRUCTOR
		//--------------------------
		/*! \brief Default constructor.
		*
		*	\since version 0.0.4
		*/
		zHcUnit();


		/*! \brief Default constructor.
		*
		*	\since version 0.0.4
		*/
		zHcUnit(zObjMesh& inMeshObj_, zFunctionType&_funcType, zStructureType&_structureType);

		//--------------------------
		//---- DESTRUCTOR
		//--------------------------

		/*! \brief Default destructor.
		*
		*	\since version 0.0.4
		*/
		~zHcUnit();


		//--------------------------
		//---- SET METHODS
		//--------------------------

		/*! \brief This method sets the edges attributes: primary or secundary and boundary conditions
		*
		*	\since version 0.0.4
		*/
		void setCellAttributes();


#ifndef ZSPACE_UNREAL_INTEROP

		/*! \brief This method sets the zModel pointer.
		*
		*	\since version 0.0.4
		*/
		void setUnitDisplayModel(zModel&_model);
#endif

		//--------------------------
		//---- CREATE METHODS
		//--------------------------


		/*! \brief This method creates structural units zHcStructure.
		*
		*	\param		[in]	_columnObjs 				- input pointer of column mesh obj
		*	\param		[in]	_slabObjs					- input pointer of slab mesh obj
		*	\since version 0.0.4
		*/
		bool createStructuralUnits(zStructureType&_structureType);

		/*! \brief This method creates internal layout.
		*
		*	\param		[in]	_layoutType					- input desired layout option
		*	\since version 0.0.4
		*/
		void importLayoutFromPath(string&_path);

		/*! \brief This method creates internal layout.
		*
		*	\param		[in]	_layoutType					- input desired layout option
		*	\since version 0.0.4
		*/
		void setLayoutByType(zLayoutType&_layout);

		/*! \brief This method creates internal studio layout.
		*
		*	\since version 0.0.4
		*/

		//--------------------------
		//---- UPDATE METHODS
		//--------------------------

		/*! \brief This method updates the structure cell in this unit.
		*
		*	\param		[in]	_celledgesAttributes					- sets the edges attributes
		*	\param		[in]	_cellBoundartAttributes					- sets the boundary attributes
		*	\param		[in]	_height									- sets the height of the cell
		*	\since version 0.0.4
		*/
		void updateStructureUnits();

		//--------------------------
		//---- DISPLAY METHODS
		//--------------------------

		/*! \brief This method creates the facades that live in this structure cell object
		*
		*	\param		[in]	_showColumns					- display column objs
		*	\since version 0.0.4
		*/
		void displayLayout(int&_index, bool&_show);



	};
}

#if defined(ZSPACE_STATIC_LIBRARY)  || defined(ZSPACE_DYNAMIC_LIBRARY)
// All defined OK so do nothing
#else
#include<source/zHousing/architecture/zHcUnit.cpp>
#endif

#endif