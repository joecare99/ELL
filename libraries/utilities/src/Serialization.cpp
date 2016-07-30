////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Project:  Embedded Machine Learning Library (EMLL)
//  File:     Serialization.cpp (utilities)
//  Authors:  Chuck Jacobs
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Serialization.h"
#include "Format.h"
#include "ISerializable.h"
#include "Variant.h"

#include <iostream>
#include <string>

namespace utilities
{
    //
    // Serialization
    //
    void Serializer::SerializeValue(const char* name, const ISerializable& value)
    {
        BeginSerializeObject(name, value);
        SerializeObject(name, value);
        EndSerializeObject(name, value);
    }

    void Serializer::BeginSerializeObject(const char* name, const ISerializable& value)
    {
        // nothing
    }

    void Serializer::EndSerializeObject(const char* name, const ISerializable& value)
    {
        // nothing
    }


    //
    // Deserialization
    //
    void Deserializer::DeserializeValue(const char* name, ISerializable& value)
    {
        auto typeName = BeginDeserializeObject(name, value);
        DeserializeObject(name, value);
        EndDeserializeObject(name, value);
    }

    std::string Deserializer::BeginDeserializeObject(const char* name, ISerializable& value)
    {
        return "";
    }

    void Deserializer::EndDeserializeObject(const char* name, ISerializable& value)
    {
        // nothing
    }
}
