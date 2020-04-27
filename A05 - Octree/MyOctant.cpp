#include "MyOctant.h"
#include <vector>
Simplex::MyOctant::MyOctant(uint a_nMaxLevel, uint a_nidealEntityCount)
{
	m_pMeshMngr->GetInstance(); 
	m_pEntityMngr->GetInstance();
	EntityCount = m_pEntityMngr->GetEntityCount();
	m_uMaxLevel = a_nMaxLevel;
	m_uIdealEntityCount = a_nidealEntityCount;

	m_lChild.clear();
	m_pRoot = this;

	m_uOctantCount++;
	//std::vector<vector3> Max;
	//std::vector<vector3> Min;
	std::vector<vector3> MinMaxVector3;
	for (int i = 0; i <= EntityCount; i++)
	{
		//m_entityList->push_back(m_pEntityMngr->GetEntityArray()[i]);
		//MyEntity Entity = m_pEntityMngr->GetEntityArray()[i];
		MyEntity* Entity = m_pEntityMngr->GetEntity(i);
		RBody = Entity->GetRigidBody();
		//Max.push_back(RBody->GetMaxGlobal());
		//Min.push_back(RBody->GetMinGlobal());
		MinMaxVector3.push_back(RBody->GetMaxGlobal());
		MinMaxVector3.push_back(RBody->GetMinGlobal());
	}
	MyRigidBody* RB = new MyRigidBody(MinMaxVector3);
	vector3 Half = RB->GetHalfWidth();
	vector3 Center = RB->GetCenterLocal();
	m_v3Center = Center;
	m_fSize = Half.x * 2.0f;
	m_v3Max = m_v3Center - Half;
	m_v3Min = m_v3Center - Half;

	//ConstructTree(m_uMaxLevel); i think this is where this goes?
}

Simplex::MyOctant::MyOctant(vector3 a_v3Center, float a_fSize)
{
	m_v3Center = a_v3Center;
	m_fSize = a_fSize;
	vector3 size = vector3(a_fSize / 2.0f);
	//m_pEntityMngr->AddDimension("D1", 0);
	//EntityCount = m_pEntityMngr->GetEntityCount();
	m_v3Min = m_v3Center - size;
	m_v3Max = m_v3Center + size;
	for(int i = 0; i <= EntityCount;i++)
	{
		//m_entityList.push_back(m_pEntityMngr->GetEntityArray()[i]);
	}
	m_uOctantCount++;
}

Simplex::MyOctant::MyOctant(MyOctant const& other)
{
	m_uOctantCount = other.m_uOctantCount;
	m_uMaxLevel = other.m_uMaxLevel;
	m_uIdealEntityCount = other.m_uIdealEntityCount;
	m_v3Center = other.m_v3Center;
	m_fSize = other.m_fSize;

	m_uID = other.m_uID;
	m_uLevel = other.m_uLevel;
	m_uChildren = m_uChildren;

	m_pMeshMngr = other.m_pMeshMngr;
	m_pEntityMngr = other.m_pEntityMngr;

	m_v3Max = other.m_v3Max;
	m_v3Min = other.m_v3Min;

	m_pParent = other.m_pParent;
	m_pChild[8] = other.m_pChild[8];

	m_entityList = other.m_entityList;

	m_pRoot = other.m_pRoot;
	m_lChild = other.m_lChild;
	EntityCount = other.EntityCount;

	RBody = other.RBody; 
}

Simplex::MyOctant& Simplex::MyOctant::operator=(MyOctant const& other)
{
	// TODO: insert return statement here
	if(this== &other)
	{
		return *this;
	}

	

	m_v3Center = other.m_v3Center;
	m_fSize = other.m_fSize;
}

Simplex::MyOctant::~MyOctant(void)
{
//	delete m_entityList[];
	//m_entityList = nullptr;
}

void Simplex::MyOctant::Swap(MyOctant& other)
{
	for (int i = 0; i <= EntityCount; i++)
	{
		m_entityList[i] = other.m_entityList[i];
	}
}

float Simplex::MyOctant::GetSize(void){	return m_fSize;}

Simplex::vector3 Simplex::MyOctant::GetCenterGlobal(void){ 	return m_v3Center;}

Simplex::vector3 Simplex::MyOctant::GetMinGlobal(void){	return m_v3Min;}

Simplex::vector3 Simplex::MyOctant::GetMaxGlobal(void){	return m_v3Max;}

bool Simplex::MyOctant::IsColliding(uint a_uRBIndex)
{
	//i heavily refrenced the iscolliding code from the given myrigidbody code
	//check if spheres are colliding
	
	//MyRigidBody RB = MyEntity* Entity.GetRigidBody
	MyEntity* Entity = m_pEntityMngr->GetEntity(a_uRBIndex);
	MyRigidBody* RB = Entity->GetRigidBody();

	vector3 max = RB->GetMaxGlobal();
	vector3 min = RB->GetMinGlobal();//global or local?

		if (max.x < min.x) //this to the right of other
			return false;
		if (min.x > max.x) //this to the left of other
			return false;

		if (max.y < min.y) //this below of other
			return false;
		if (min.y > max.y) //this above of other
			return false;

		if (max.z < min.z) //this behind of other
			return false;
		if (min.z > max.z) //this in front of other
			return false;

	
		return true;
}

void Simplex::MyOctant::Display(uint a_nIndex, vector3 a_v3Color)
{

}

void Simplex::MyOctant::Display(vector3 a_v3Color)
{
	m_pMeshMngr->AddCubeToRenderList(,a_v3Color)

}

void Simplex::MyOctant::DisplayLeafs(vector3 a_v3Color)
{
}

void Simplex::MyOctant::ClearEntityList(void)
{
	m_entityList.clear();
}

void Simplex::MyOctant::Subdivide(void)
{

	if (m_uChildren > 0)
		return;
	vector3 center = m_v3Center;
	float CX = center.x;
	float CY = center.y;
	float CZ = center.z;

	float quad = m_fSize / 4;
	//top front right 
	m_pChild[0] = new MyOctant(vector3(CX + quad,CY + quad,CZ + quad),m_fSize);
	//top front left
	m_pChild[1] = new MyOctant(vector3(CX - quad, CY + quad, CZ + quad), m_fSize);
	//top back Left
	m_pChild[2] = new MyOctant(vector3(CX - quad, CY + quad, CZ - quad), m_fSize);
	//top back right 
	m_pChild[3] = new MyOctant(vector3(CX + quad, CY + quad, CZ - quad), m_fSize);
	//bottom back right
	m_pChild[4] = new MyOctant(vector3(CX + quad, CY - quad, CZ - quad), m_fSize);
	//bottom back left
	m_pChild[5] = new MyOctant(vector3(CX - quad, CY - quad, CZ - quad), m_fSize);
	//bottom front left 
	m_pChild[6] = new MyOctant(vector3(CX - quad, CY - quad, CZ + quad), m_fSize);
	//bottom front right 
	m_pChild[7] = new MyOctant(vector3(CX + quad, CY - quad, CZ + quad), m_fSize);

	m_uChildren = 8;
	for (int i = 0; i < m_uChildren; i++) {
		m_pChild[i]->m_pParent = this;
		m_pChild[i]->m_pRoot = this->m_pRoot;
		m_pChild[i]->m_uLevel++;
	
	}



}

Simplex::MyOctant* Simplex::MyOctant::GetChild(uint a_nChild){	return m_pChild[8];}

Simplex::MyOctant* Simplex::MyOctant::GetParent(void){	return m_pParent;}

bool Simplex::MyOctant::IsLeaf(void)
{
	if(m_uChildren == 0)
	{
		return true;
	}else
	{
		return false;
	}
}

bool Simplex::MyOctant::ContainsMoreThan(uint a_nEntities)
{

}

void Simplex::MyOctant::KillBranches(void)
{
}

void Simplex::MyOctant::ConstructTree(uint a_nMaxLevel)
{
}

void Simplex::MyOctant::AssignIDtoEntity(void)
{
}

Simplex::uint Simplex::MyOctant::GetOctantCount(void)
{
	return m_uOctantCount;
}

void Simplex::MyOctant::Release(void)
{
}

void Simplex::MyOctant::Init(void)
{
}

void Simplex::MyOctant::ConstructList(void)
{
}
