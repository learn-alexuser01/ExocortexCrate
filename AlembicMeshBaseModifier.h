#ifndef __ALEMBIC_MESH_BASE_MODIFIER__H
#define __ALEMBIC_MESH_BASE_MODIFIER__H

#include "Foundation.h"  
#include <MNMath.h>
#include <iparamb2.h>
#include <PolyObj.h>
#include "resource.h"
#include "surf_api.h"
#include <string>
#include "AlembicDefinitions.h"
#include "AlembicMeshUtilities.h"
#include "AlembicNames.h"


class AlembicMeshBaseModifier : public Modifier {
public:
	IParamBlock2 *pblock;
	
	// Parameters in first block:
	enum 
	{ 
		ID_PATH,
		ID_IDENTIFIER,
		ID_TIME,
		ID_TOPOLOGY,
		ID_GEOMETRY,
		ID_GEOALPHA,
		ID_NORMALS,
		ID_UVS,
		ID_MUTED
	};

	static IObjParam *ip;
	static AlembicMeshBaseModifier *editMod;

	AlembicMeshBaseModifier();

	// From Animatable
	virtual Class_ID ClassID() { return ALEMBIC_MESH_BASE_MODIFIER_CLASSID; }		
	void GetClassName(TSTR& s) { s = _T("Alembic Mesh Base Modifier"); }  
	TCHAR *GetObjectName() { return _T("Alembic Mesh Base Modifier"); }

	void DeleteThis() { delete this; }
	RefTargetHandle Clone(RemapDir& remap);

	// From Modifier
	ChannelMask ChannelsUsed()  { return TOPO_CHANNEL|GEOM_CHANNEL|TEXMAP_CHANNEL; }
	ChannelMask ChannelsChanged() { return TOPO_CHANNEL|GEOM_CHANNEL|TEXMAP_CHANNEL; }
	Class_ID InputType() { return polyObjectClassID; }
	void ModifyObject (TimeValue t, ModContext &mc, ObjectState *os, INode *node);
	//Interval LocalValidity(TimeValue t) { return GetValidity(t); }
	//Interval GetValidity (TimeValue t);
	BOOL DependOnTopology(ModContext &mc) { return TRUE; }

	// From BaseObject
	CreateMouseCallBack* GetCreateMouseCallBack() {return NULL;} 

	void BeginEditParams( IObjParam  *ip, ULONG flags,Animatable *prev);
    void EndEditParams( IObjParam *ip, ULONG flags,Animatable *next);

	int NumParamBlocks () { return 1; }
	IParamBlock2 *GetParamBlock (int i) { return pblock; }
	IParamBlock2 *GetParamBlockByID (short id) { return (pblock->ID() == id) ? pblock : NULL; }

	int NumRefs() { return 1; }
	RefTargetHandle GetReference(int i) { return pblock; }

	int NumSubs() { return 1; }
	Animatable* SubAnim(int i) { return GetReference(i); }
	TSTR SubAnimName(int i) { return _T("IDS_PROPS"); }

	RefResult NotifyRefChanged( Interval changeInt,RefTargetHandle hTarget, 
		PartID& partID, RefMessage message);

private:
	virtual void SetReference(int i, RefTargetHandle rtarg) { pblock = (IParamBlock2 *) rtarg; }
};



class AlembicMeshBaseModifierClassDesc : public ClassDesc2
{
public:
	AlembicMeshBaseModifierClassDesc() {}
	~AlembicMeshBaseModifierClassDesc() {}

	int 			IsPublic()		{ return TRUE; }
	const TCHAR *	ClassName()		{ return _T("Alembic Mesh Base Modifier"); }
	SClass_ID		SuperClassID()	{ return OSM_CLASS_ID; }
	void *			Create(BOOL loading = FALSE) { return new AlembicMeshBaseModifier; }
	Class_ID		ClassID()		{ return ALEMBIC_MESH_BASE_MODIFIER_CLASSID; }
	const TCHAR* 	Category()		{ return EXOCORTEX_ALEMBIC_CATEGORY; }
	const TCHAR*	InternalName()	{ return _T("AlembicMeshBaseModifier"); }	// returns fixed parsable name (scripter-visible name)
	HINSTANCE		HInstance()		{ return hInstance; }			// returns owning module handle
};

ClassDesc2 *GetAlembicMeshBaseModifierClassDesc();

#endif
