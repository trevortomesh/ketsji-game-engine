/*
 * ***** BEGIN GPL LICENSE BLOCK *****
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * The Original Code is Copyright (C) 2001-2002 by NaN Holding BV.
 * All rights reserved.
 *
 * The Original Code is: all of this file.
 *
 * Contributor(s): none yet.
 *
 * ***** END GPL LICENSE BLOCK *****
 */

/** \file SCA_AddObjectActuator.h
 *  \ingroup gamelogic
 */

#ifndef __SCA_ADDOBJECTACTUATOR_H__
#define __SCA_ADDOBJECTACTUATOR_H__

#include "SCA_IActuator.h"
#include "SCA_LogicManager.h"

#include "MT_Vector3.h"


class SCA_IScene;

class SCA_AddObjectActuator : public SCA_IActuator
{
	Py_Header

private:
	/// Time field: lifetime of the new object
	float m_timeProp;

	/// Original object reference (object to replicate)
	SCA_IObject *m_OriginalObject;

	/// Object will be added to the following scene
	SCA_IScene *m_scene;

	/// Linear velocity upon creation of the object. 
	float m_linear_velocity[3];

	/// Apply the velocity locally 
	bool m_localLinvFlag;
	
	/// Angular velocity upon creation of the object. 
	float m_angular_velocity[3];

	/// Apply the velocity locally 
	bool m_localAngvFlag; 

	SCA_IObject *m_lastCreatedObject;

public:

	/** 
	 * This class also has the default constructors
	 * available. Use with care!
	 */

	SCA_AddObjectActuator(SCA_IObject *gameobj,
	                      SCA_IObject *original,
	                      float time,
	                      SCA_IScene *scene,
	                      const float *linvel,
	                      bool linv_local,
	                      const float *angvel,
	                      bool angv_local);

	~SCA_AddObjectActuator(void);

	CValue *GetReplica();

	virtual void ProcessReplica();

	virtual void Replace_IScene(SCA_IScene *val)
	{
		m_scene = val;
	}

	virtual bool UnlinkObject(SCA_IObject *clientobj);

	virtual void Relink(std::map<void *, void *> &obj_map);

	virtual bool Update();

	SCA_IObject *GetLastCreatedObject() const;

	void InstantAddObject();

#ifdef WITH_PYTHON

	KX_PYMETHOD_DOC_NOARGS(SCA_AddObjectActuator, InstantAddObject);

	static PyObject *pyattr_get_object(void *self, const struct KX_PYATTRIBUTE_DEF *attrdef);
	static int pyattr_set_object(void *self, const struct KX_PYATTRIBUTE_DEF *attrdef, PyObject *value);
	static PyObject *pyattr_get_objectLastCreated(void *self, const struct KX_PYATTRIBUTE_DEF *attrdef);
	
#endif  /* WITH_PYTHON */

}; /* end of class SCA_AddObjectActuator : public SCA_EditObjectActuator */

#endif  /* __SCA_ADDOBJECTACTUATOR_H__ */
