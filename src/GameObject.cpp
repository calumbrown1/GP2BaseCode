//
//  GameObject.cpp
//  GP2BaseCode
//
//  Created by Brian on 31/10/2014.
//  Copyright (c) 2014 Glasgow Caledonian University. All rights reserved.
//

#include "GameObject.h"
#include "Component.h"
#include "Transform.h"
#include "Mesh.h"
#include "Material.h"
#include "Camera.h"
#include "Light.h"

GameObject::GameObject()
{
    m_Transform=NULL;
    m_Mesh=NULL;
    m_Material=NULL;
    m_Camera=NULL;
	m_Light = NULL;
    m_Name="GameObject";
}

GameObject::~GameObject()
{
    
}

void GameObject::init()
{
	for (auto iter = m_Components.begin(); iter != m_Components.end(); iter++)
	{
		(*iter)->init();
	}
    
}

void GameObject::update()
{
	for (auto iter = m_Components.begin(); iter != m_Components.end(); iter++)
	{
		(*iter)->update();
	}
    
}

void GameObject::render()
{
	for (auto iter = m_Components.begin(); iter != m_Components.end(); iter++)
	{
		(*iter)->render();
	}
    
}

void GameObject::destroy()
{
    auto iter=m_Components.begin();
	while(iter!=m_Components.end())
    {
        (*iter)->destroy();
        if ((*iter))
        {
            delete (*iter);
            (*iter)=NULL;
            iter=m_Components.erase(iter);
        }
        else
        {
            iter++;
        }
    }
    m_Components.clear();
    
}

void GameObject::addComponent(Component * component)
{
    component->setParent(this);
    m_Components.push_back(component);
}

void GameObject::setName(const std::string& name)
{
    m_Name=name;
}

const std::string& GameObject::getName()
{
    return m_Name;
}

void GameObject::setTransform(Transform * transform)
{
    m_Transform=transform;
    addComponent(transform);
}

void GameObject::setMesh(Mesh * mesh)
{
    m_Mesh=mesh;
    addComponent(mesh);
}

void GameObject::setMaterial(Material * material)
{
    m_Material=material;
    addComponent(material);
}

void GameObject::setCamera(Camera * camera)
{
    m_Camera=camera;
    addComponent(camera);
}

void GameObject::setLight(Light * light)
{
	m_Light = light;
	addComponent(light);
}

Transform * GameObject::getTransform()
{
    return m_Transform;
}

Mesh * GameObject::getMesh()
{
    return m_Mesh;
}

Material * GameObject::getMaterial()
{
    return m_Material;
}

Camera * GameObject::getCamera()
{
    return m_Camera;
}

Light * GameObject::getLight()
{
	return m_Light;
}
