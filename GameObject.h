#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include <list>
#include <vector>
#include "imgui.h"
#include "assert.h"
#include "Globals.h"
#include "assimp/matrix4x4.h"
#include "Math/float4x4.h"
#include "Geometry/AABB.h"

class Component;
class ComponentTransform;
enum class ComponentType;

class GameObject
{
	public:
		GameObject();
		GameObject(const char* goName, const aiMatrix4x4& transform, const char* fileLocation);
		GameObject(const char* goName, const aiMatrix4x4& transform, GameObject* goParent, const char* fileLocation);
		GameObject(const GameObject& duplicateGameObject);
		~GameObject();

		void					Update();
		void					Draw() const;
		void					CleanUp();
		void					DrawProperties();
		void					DrawHierarchy(GameObject* goSelected);
		void					DrawBBox() const;
		std::string				GetFileFolder() const;

		Component*				AddComponent(ComponentType type);
		void					RemoveComponent(Component* component);
		Component*				GetComponent(ComponentType type) const;
		std::vector<Component*> GetComponents(ComponentType type) const;

		void					BatmanizeGameObject(GameObject* batman);

		AABB					ComputeBBox() const;

		math::float4x4			GetLocalTransform() const;
		math::float4x4			GetGlobalTransform() const;
		void					ModelTransform(unsigned shader) const;


	public:
		bool					enabled = true;
		bool					drawGOBBox = false;
		bool					drawChildsBBox = false;
		bool					duplicating = false;
		const char*				filePath = nullptr;
		const char*				name = "GameObject";
		GameObject*				parent = nullptr;
		std::vector<Component*>	components;
		std::list<GameObject*>	goChilds;

		ComponentTransform*		transform = nullptr;
		AABB&					bbox = AABB();

		bool					toBeDeleted = false;
		bool					toBeCopied = false;

};

#endif
