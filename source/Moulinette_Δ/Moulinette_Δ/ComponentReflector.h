#pragma once
#include"VRAnalog.h"
#include"VRComponent.h"
#include"VRRelative.h"
#include "VRBoolean.h"
#include "VRQuaternion.h"

/// <summary>
/// Le componentReflector est un �l�ment statique permettant d'int�ragir avec un sous-type du VRComponent correctement.
/// Il agit de mani�re similaire au reflecteur C# et va caster dynamiquement le composant au type voulu en fonction d'un identifiant
/// que le VRComponent a par d�faut (et qui est modifi� par les constructeurs des h�ritants) [sclType]
/// </summary>
static class ComponentReflector {
private:
public:
	/// <summary>
	/// Va donner des donn�es au composant s�lectionn�
	/// </summary>
	/// <param name="component"> le composant avec lequel on veut int�ragir</param>
	/// <param name="data"> les donn�es sous forme de string</param>
	static void provideDataToComponent(VRComponent* component, string data);
	/// <summary>
	/// Va demander des donn�es au composant s�lectionn� en appellant son to_string()
	/// </summary>
	/// <param name="component"> le composant qui contient les donn�es voulues</param>
	/// <returns></returns>
	static string requestDataFromComponent(VRComponent* component);
};