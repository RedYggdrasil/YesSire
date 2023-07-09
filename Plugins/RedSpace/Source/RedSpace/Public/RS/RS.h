// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

inline const FString EMPTY_FSTRING = "";
inline const FString R_UNKNOWN = "UNKNOWN";

#define PBool(value) (*FString((value)?"True":"False"))
#define PName(value) (*((IsValid(value))?value->GetName():FString(value == nullptr ? "nullptr":"invalidObject")))
#define IPName(value) ( *( (value != nullptr && IsValid(value->_getUObject())) ? value->_getUObject()->GetName() : FString(value == nullptr ? "nullptr":"invalidObject") ) )

#define L_PATH __FILE__ "(" PREPROCESSOR_TO_STRING(__LINE__) "): "
//#define R_ABSTRACT(rValue) { check(0 && "Abstract function must be implement  in all child class"); return rValue; }
#define R_ABSTRACT(rValue, name) { check(0 && "The abstract function " name " must be implement  in all child class"); return rValue; }

