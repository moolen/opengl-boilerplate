#ifndef BOILERPLATE_SCENE_CPP
#define BOILERPLATE_SCENE_CPP

#include "scene.h"
#include <glm/ext.hpp>
#include "../util/file.h"
#include <iostream>


Scene::Scene(
	const char* name,
	Camera* camera,
	Inputhandler* inputhandler
):
	m_name(name),
	m_camera(camera),
	m_loader(Loader()),
	m_entityFactory(EntityFactory()),
	m_path("resources/scenes/"),
	m_inputHandler(inputhandler)
{

	m_entityFactory.SetLoader(&m_loader);

	// read & parse configuration
	std::string fullPath = m_path + std::string(m_name);
	File configuration(fullPath.c_str());
	rapidjson::Document document;
	document.Parse(configuration.Get().c_str());

	// parse lights
	if( document["lights"].IsArray() ){
		// iterate over array
		for(rapidjson::SizeType i = 0; i < document["lights"].Size(); i++){
				
				// defaults for pos & color
				glm::vec3 lightPosition = glm::vec3(0, 0, 0);
				glm::vec3 lightColor = glm::vec3(0, 0, 0);
				bool addLight = true;

				// iterate over object keys
				
				rapidjson::Value::ConstMemberIterator posItr = document["lights"][i].FindMember("position");
				if( posItr != document["lights"][i].MemberEnd() ){
					for(rapidjson::SizeType j = 0; j < posItr->value.Size(); j++){
						if( j == 0 ){
							lightPosition.x = posItr->value[j].GetDouble();
						}else if(j == 1){
							lightPosition.y = posItr->value[j].GetDouble();
						}else if(j == 2){
							lightPosition.z = posItr->value[j].GetDouble();
						}else{
							std::cout << "could not find lightPosition for j=" << j << std::endl;
							addLight = false;
						}
					}
				}

				rapidjson::Value::ConstMemberIterator colorItr = document["lights"][i].FindMember("color");
				
				// color
				if( colorItr != document["lights"][i].MemberEnd() ){
					for(rapidjson::SizeType j = 0; j < colorItr->value.Size(); j++){
						if( j == 0 ){
							lightColor.r = colorItr->value[j].GetDouble();
						}else if(j == 1){
							lightColor.g = colorItr->value[j].GetDouble();
						}else if(j == 2){
							lightColor.b = colorItr->value[j].GetDouble();
						}else{
							std::cout << "could not find lightColor for i=" << i << std::endl;
							addLight = false;
						}
					}
				}

				// if everything is valid... add light
				if( addLight == true){
					AddLight(lightPosition, lightColor);
				}else{
					std::cout << "dont adding light: missing values for pos or color" << std::endl;
				}

		}
	}else{
		std::cout << "no lights object found in " << m_name << std::endl;
	}

	if( document.HasMember("entities") && document["entities"].IsArray() ){

		glm::vec3 position;
		std::string meshType;
		std::string mesh;
		std::string texture;
		std::string fragmentShader;
		std::string vertexShader;

		for(rapidjson::SizeType i = 0; i < document["entities"].Size(); i++){
			if( document["entities"][i].IsObject() ){
				
				//positon
				rapidjson::Value::ConstMemberIterator posItr = document["entities"][i].FindMember("position");
				if( posItr != document["entities"][i].MemberEnd() ){
					for(rapidjson::SizeType j = 0; j < posItr->value.Size(); j++){
						if( j == 0 ){
							position.x = posItr->value[j].GetDouble();
						}else if(j == 1){
							position.y = posItr->value[j].GetDouble();
						}else if(j == 2){
							position.z = posItr->value[j].GetDouble();
						}else{
							std::cout << "could not find position for entity i=" << i << std::endl;
						}
					}
				}else{
					std::cout << "meshType property not found in entity #" << i << std::endl;
				}

				//meshType
				rapidjson::Value::ConstMemberIterator meshTypeItr = document["entities"][i].FindMember("meshType");
				if( meshTypeItr != document["entities"][i].MemberEnd() ){
					meshType = meshTypeItr->value.GetString();
				}else{
					std::cout << "meshType property not found in entity #" << i << std::endl;
				}

				//mesh
				rapidjson::Value::ConstMemberIterator meshItr = document["entities"][i].FindMember("mesh");
				if( meshItr != document["entities"][i].MemberEnd() ){
					mesh = meshItr->value.GetString();
				}else{
					std::cout << "mesh property not found in entity #" << i << std::endl;
				}

				//texture
				rapidjson::Value::ConstMemberIterator textureItr = document["entities"][i].FindMember("texture");
				if( textureItr != document["entities"][i].MemberEnd() ){
					texture = textureItr->value.GetString();
				}else{
					std::cout << "texture property not found in entity #" << i << std::endl;
				}

				// shader
				if( document["entities"][i].HasMember("shader") ){
					for( rapidjson::Value::ConstMemberIterator shaderItr = document["entities"][i]["shader"].MemberBegin();
					shaderItr != document["entities"][i]["shader"].MemberEnd(); ++shaderItr )
					{
						if(shaderItr->name.GetString() == std::string("vertex") ){
							vertexShader = shaderItr->value.GetString();
						}

						if( shaderItr->name.GetString() == std::string("fragment") ){
							fragmentShader = shaderItr->value.GetString();
						}
					}
				}

				m_entityFactory.CreateEntity(
					position,
					meshType,
					mesh,
					texture,
					fragmentShader,
					vertexShader
				);

			}else{
				std::cout << "entity #" << i << " is not an object" << std::endl;
			}
		}

	}else{
		std::cout << "no entities objects found in " << m_name << std::endl;
	}

	

}

void Scene::Render(){

	std::vector<Entity> entities = m_entityFactory.GetEntities();
	for( std::vector<Entity>::iterator it = entities.begin(); it != entities.end(); ++it ){
		it->Render(m_camera);
	}

}

void Scene::AddLight(glm::vec3 pos, glm::vec3 color){
	std::cout << "adding light; position: " << glm::to_string(pos) << std::endl;
	std::cout << "adding light; color: " << glm::to_string(color) << std::endl;
	m_lights.push_back(Light(pos, color));
}

Scene::~Scene(){

}

#endif