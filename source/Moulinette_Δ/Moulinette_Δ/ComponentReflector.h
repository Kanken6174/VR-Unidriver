#pragma once
#include"VRAnalog.h"
#include"VRComponent.h"
#include"VRRelative.h"
#include "VRBoolean.h"
#include "VRQuaternion.h"

/// <summary>
/// Le componentReflector est un élément statique permettant d'intéragir avec un sous-type du VRComponent correctement.
/// Il agit de manière similaire au reflecteur C# et va caster dynamiquement le composant au type voulu en fonction d'un identifiant
/// que le VRComponent a par défaut (et qui est modifié par les constructeurs des héritants) [sclType]
/// </summary>
static class ComponentReflector {
private:
public:
	/// <summary>
	/// Va donner des données au composant sélectionné
	/// </summary>
	/// <param name="component"> le composant avec lequel on veut intéragir</param>
	/// <param name="data"> les données sous forme de string</param>
	static void provideDataToComponent(VRComponent* component, string data);
	/// <summary>
	/// Va demander des données au composant sélectionné en appellant son to_string()
	/// </summary>
	/// <param name="component"> le composant qui contient les données voulues</param>
	/// <returns></returns>
	static string requestDataFromComponent(VRComponent* component);
};