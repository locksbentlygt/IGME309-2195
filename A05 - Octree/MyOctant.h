#ifndef _MYOCTANTCLASS_H_
#define _MYOCTANTCLASS_H_

#include "MyEntityManager.h"



namespace Simplex
{
//system class 
class MyOctant
{
	 
	static uint m_uOctantCount; // will store the number of octants initiated 
	static uint m_uMaxLevel; //stores the maximum level an octant can go to 
	static uint m_uIdealEntityCount; //will tell how many ideal entities this object will contain 

	uint m_uID = 0; //Will store the current id for this octant 
	uint m_uLevel = 0; //will store the current level of the octant
	uint m_uChildren = 0; //number of children on the octant (either 0 or 6)

	float m_fSize = 0.0f; //size of the octant

	MeshManager* m_pMeshMngr = nullptr;//mesh manager singleton 
	MyEntityManager* m_pEntityMngr = nullptr; //entity manager singleton 

	vector3 m_v3Center = vector3(0.0f); //stores the center point of the octant
	vector3 m_v3Min = vector3(0.0f); //will store the minimum vector of the octant
	vector3 m_v3Max = vector3(0.0f); //will store the maximum vector of the octant 

	MyOctant* m_pParent = nullptr; //will store the parent of the current octant 
	MyOctant* m_pChild[8]; //stores the children of the current octant 

	std::vector<uint> m_entityList; // list of entities under this octant (index in entity manager)

	MyOctant* m_pRoot = nullptr;//root octant 
	std::vector<MyOctant*> m_lChild; //list of nodes that contain cetain objects 
	uint EntityCount; //the ammount of entities in the scene
	
	MyRigidBody* RBody;

	bool m_treeReady = false;
	bool m_treeBuilt = false;

public:
	/*
	USAGE: COnstructor, will create an octant containing all MagnaEntities Instances in the mesh 
	manager currently contained 
	ARGUMENTS
	- uint a_nMaxLevel = 2 -> sets the maximum level of subdivisions 
	- uint nIdealEntityCOunt = 5 sets the ideal level of objects per octant
	OUTPUT: class object 
	*/
	MyOctant(uint a_nMaxLevel = 2, uint a_nidealEntityCount = 5);
	/*
	USAGE: COnstructor
	ARGUMENTS
	- vector3 a_v3Center -> center of the octant in global space
	- float a_fSize size of each side of the octant volume
	OUTPUT: class object
	*/
	MyOctant(vector3 a_v3Center, float a_fSize);
	/*
	USAGE:Copy Constructor 
	ARGUMENTS: Class object to copy 
	OUTPUT: class object instance 
	*/
	MyOctant(MyOctant const& other);
	/*
	USAGE:Copy Assignment Operator
	ARGUMENTS: Class object to copy 
	OUTPUT: ----
	*/
	MyOctant& operator=(MyOctant const& other);
	/*
	USAGE:Destructor
	ARGUMENTS: ----
	OUTPUT:---
	*/
	~MyOctant(void);
	/*
	USAGE:Changes the object contents for other objects
	ARGUMENTS: MyOctant& other -> object to swap content from
	OUTPUT:---
	*/
	void Swap(MyOctant& other);
	/*
	USAGE:Get this octants size 
	ARGUMENTS: ----
	OUTPUT:size of octant
	*/
	float GetSize(void);
	/*
	USAGE:gets the center of the octant in global space
	ARGUMENTS: ----
	OUTPUT:center of the octant in global space 
	*/
	vector3 GetCenterGlobal(void);
	/*
	USAGE:Gets the min corner of the octant in global space 
	ARGUMENTS: ----
	OUTPUT:minimum in global space 
	*/
	vector3 GetMinGlobal(void);
	/*
	USAGE:Gets the max corner of the octant in global space
	ARGUMENTS: ----
	OUTPUT:maximum in global space
	*/
	vector3 GetMaxGlobal(void);
	/*
	USAGE:Asks if there is a collision with the entity specified by index from the 
	Bounding object manager 
	ARGUMENTS: 
		- int a_uRBIndex -> index of the entity in the entity manager
	OUTPUT:check of the collision 
	*/
	bool IsColliding(uint a_uRBIndex);
	/*
	USAGE: Displays the MyOctant volume specified by index including the objects underneath
	ARGUMENTS:
		- unit a_nIndex -> MyOctant to be displayed 
		- vector3 a_v3Color = REGREEN -> Color of the volume to display
	OUTPUT:---
*/
	void Display(uint a_nIndex, vector3 a_v3Color = C_GREEN);
	/*
	USAGE: Displays the MyOctant volume in the color specified 
	ARGUMENTS:
		- vector3 a_v3Color = REGREEN -> Color of the volume to display 
	OUTPUT:
	*/
	void Display(vector3 a_v3Color = C_GREEN);
	/*
	USAGE: Displays the non empty leafs i nthe octree
	ARGUMENTS:
		- vector3 a_v3Color = REGREEN -> Color of the volume to display
	OUTPUT:---
	*/
	void DisplayLeafs(vector3 a_v3Color = C_GREEN);
	/*
	USAGE: Clears the entity list for each node
	ARGUMENTS:
		-
	OUTPUT:
	*/
	void ClearEntityList(void);
	/*
	USAGE: allocates 8 smaller octants in the child pointers 
	ARGUMENTS:
		-
	OUTPUT:
	*/
	void Subdivide(void);
	/*
	USAGE: returns the child specified in the index
	ARGUMENTS:
		- uint a_nChild -> index of the child (from 0 to 7)
	OUTPUT: MyOctant object (child in index)
	*/
	MyOctant* GetChild(uint a_nChild);
	/*
	USAGE: returns the parent of the octant
	ARGUMENTS:
		-
	OUTPUT: MyOctant objet(Parnet)
	*/
	MyOctant* GetParent(void);
	/*
	USAGE: Asks the MyOctant if it does not contain any children (its a leaf)
	ARGUMENTS:
		-
	OUTPUT: it contains no chiildren 
	*/
	bool IsLeaf(void);
	/*
	USAGE: Asks the MyOctant if it contains more than this many bounding objects
	ARGUMENTS:
		- uint a_nEntities -> number of entities to query
	OUTPUT: it contains at least this many entities
	*/
	bool ContainsMoreThan(uint a_nEntities);
	/*
	USAGE: Deletes all children and the children of their children 
	ARGUMENTS:
		-
	OUTPUT:
	*/
	void KillBranches(void);
	/*
	USAGE: creates a tree using subdivisions, the max number of objects and levels 
	ARGUMENTS:
		- uint a_nMaxLevel = 3 -> sets the max level of the tree when constructing it 
	OUTPUT:
	*/
	void ConstructTree(uint a_nMaxLevel = 3);
	/*
	USAGE: Traverse the tree up to the leafs and sets the objects in them to the index 
	ARGUMENTS:
		- 
	OUTPUT:
	*/
	void AssignIDtoEntity(void);
	/*
	USAGE:get the total number of octants in the world 
	ARGUMENTS:
		- 
	OUTPUT:
	*/
	uint GetOctantCount(void);
private:
	/*
	USAGE: Deallocates member fields 
	ARGUMENTS:---
		-
	OUTPUT:---
	*/
	void Release(void);
	/*
	USAGE:Allocates member fields 
	ARGUMENTS:---
		-
	OUTPUT:---
	*/
	void Init(void);
	/*
	USAGE: creates the list of all leafs that contain objects
	ARGUMENTS:
		-
	OUTPUT:
	*/
	void ConstructList(void);
};//class

}//namespace

#endif // !_MYOCTANTCLASS_H_

	/*
	USAGE:
	ARGUMENTS:
		- 
	OUTPUT:
	*/