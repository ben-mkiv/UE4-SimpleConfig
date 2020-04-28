// all rights reserved

#include "ConfigFile.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Misc/DefaultValueHelper.h"


UConfigFile::UConfigFile(){ //FString path
}

UConfigFile::UConfigFile(const FObjectInitializer &whatever){ //FString path
}

FString *UConfigFile::getElement(const FString name){
    FString* cData = data.FindByPredicate([name](const FString& Str){
        return Str.StartsWith(name+":");
    });
    
    if(cData != nullptr){
        cData->RemoveFromStart(name + ":");
    }
    
    return cData;
}

int32 UConfigFile::getElementIndex(const FString name){
    int32 index = data.IndexOfByPredicate([name](const FString& Str){
        return Str.StartsWith(name + ":");
    });

    return index;
}

void UConfigFile::writeField(const FString name, const FString text){
    int32 currentIndex = getElementIndex(name);

    if(currentIndex != INDEX_NONE){
        data.RemoveAt(currentIndex);
    }

    data.Add(name+":"+text);
}

/** loads a file and provides a ConfigFile Object with cached data */
UConfigFile * UConfigFile::loadConfig(const FString in_path) {
    FString finalPath = FPaths::ConvertRelativePathToFull(FPaths::ProjectConfigDir() + "/" + in_path);

    UConfigFile *obj = NewObject<UConfigFile>();

    obj->path = finalPath;
    obj->succeed = FPaths::FileExists(obj->path) ? FFileHelper::LoadFileToStringArray(obj->data, *obj->path) : FFileHelper::SaveStringToFile("", *obj->path);

    return obj;
}

/** saves all changes on the provided ConfigFile Object to disk */
void UConfigFile::saveConfig(){
    FFileHelper::SaveStringArrayToFile(data, *path);
}

/** writes a boolean to the provided ConfigFile Object */
void UConfigFile::readBoolean(const FString name, const bool defaultValue, bool &value){
    FString *cData = getElement("b_"+name);

    value = (cData != nullptr) ? cData->Equals(TEXT("true"), ESearchCase::IgnoreCase) : defaultValue;
}

/** reads a boolean from the provided ConfigFile Object */
void UConfigFile::writeBoolean(const FString name, const bool value){
    writeField("b_"+name, (value == true ? "true" : "false"));
}

/** reads a string from the provided ConfigFile Object */
void UConfigFile::readString(const FString name, const FString defaultValue, FString &value){
    FString *cData = getElement("b_"+name);

    value = (cData != nullptr) ? *cData : defaultValue;
}

/** writes a string to the provided ConfigFile Object */
void UConfigFile::writeString(const FString name, const FString value){
    writeField(name, value);
}

/** reads a integer from the provided ConfigFile Object */
void UConfigFile::readInteger(const FString name, const int defaultValue, int &value){
    FString *cData = getElement("i_"+name);

    if(cData != nullptr)
        FDefaultValueHelper::ParseInt(*cData, value);
    else
        value = defaultValue;
}

/** writes a integer from the provided ConfigFile Object */
void UConfigFile::writeInteger(const FString name, const int value){
    writeField("i_"+name, FString::FromInt(value));
}

/** reads a float value from the provided ConfigFile Object */
void UConfigFile::readFloat(const FString name, const float defaultValue, float &value){
    FString *cData = getElement("f_"+name);

    if(cData != nullptr)
        FDefaultValueHelper::ParseFloat(*cData, value);
    else
        value = defaultValue;
}

/** writes a float value to the provided ConfigFile Object */
void UConfigFile::writeFloat(const FString name, const float value){
    writeField("f_"+name, FString::SanitizeFloat(value));
}