// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef MYPROJECT_Weapons_generated_h
#error "Weapons.generated.h already included, missing '#pragma once' in Weapons.h"
#endif
#define MYPROJECT_Weapons_generated_h

#define MyProject_Source_MyProject_Weapons_h_21_SPARSE_DATA
#define MyProject_Source_MyProject_Weapons_h_21_RPC_WRAPPERS
#define MyProject_Source_MyProject_Weapons_h_21_RPC_WRAPPERS_NO_PURE_DECLS
#define MyProject_Source_MyProject_Weapons_h_21_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAWeapons(); \
	friend struct Z_Construct_UClass_AWeapons_Statics; \
public: \
	DECLARE_CLASS(AWeapons, AItem, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/MyProject"), NO_API) \
	DECLARE_SERIALIZER(AWeapons)


#define MyProject_Source_MyProject_Weapons_h_21_INCLASS \
private: \
	static void StaticRegisterNativesAWeapons(); \
	friend struct Z_Construct_UClass_AWeapons_Statics; \
public: \
	DECLARE_CLASS(AWeapons, AItem, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/MyProject"), NO_API) \
	DECLARE_SERIALIZER(AWeapons)


#define MyProject_Source_MyProject_Weapons_h_21_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AWeapons(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AWeapons) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AWeapons); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AWeapons); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AWeapons(AWeapons&&); \
	NO_API AWeapons(const AWeapons&); \
public:


#define MyProject_Source_MyProject_Weapons_h_21_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AWeapons(AWeapons&&); \
	NO_API AWeapons(const AWeapons&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AWeapons); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AWeapons); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AWeapons)


#define MyProject_Source_MyProject_Weapons_h_21_PRIVATE_PROPERTY_OFFSET
#define MyProject_Source_MyProject_Weapons_h_18_PROLOG
#define MyProject_Source_MyProject_Weapons_h_21_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	MyProject_Source_MyProject_Weapons_h_21_PRIVATE_PROPERTY_OFFSET \
	MyProject_Source_MyProject_Weapons_h_21_SPARSE_DATA \
	MyProject_Source_MyProject_Weapons_h_21_RPC_WRAPPERS \
	MyProject_Source_MyProject_Weapons_h_21_INCLASS \
	MyProject_Source_MyProject_Weapons_h_21_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define MyProject_Source_MyProject_Weapons_h_21_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	MyProject_Source_MyProject_Weapons_h_21_PRIVATE_PROPERTY_OFFSET \
	MyProject_Source_MyProject_Weapons_h_21_SPARSE_DATA \
	MyProject_Source_MyProject_Weapons_h_21_RPC_WRAPPERS_NO_PURE_DECLS \
	MyProject_Source_MyProject_Weapons_h_21_INCLASS_NO_PURE_DECLS \
	MyProject_Source_MyProject_Weapons_h_21_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> MYPROJECT_API UClass* StaticClass<class AWeapons>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID MyProject_Source_MyProject_Weapons_h


#define FOREACH_ENUM_EWEAPONSTATE(op) \
	op(EWeaponState::EWS_Pickup) \
	op(EWeaponState::EWS_Equipped) \
	op(EWeaponState::EWS_Max) 

enum class EWeaponState : uint8;
template<> MYPROJECT_API UEnum* StaticEnum<EWeaponState>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
