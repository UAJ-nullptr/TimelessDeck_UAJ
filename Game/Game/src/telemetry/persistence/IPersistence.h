#pragma once
#include "queue"
#include "../serialization/ISerializer.h"
#include "../events/GenericEvent.h"

enum SerializerType {
	JSON_SER,
	CSV_SER,
	YAML_SER
};

class IPersistence
{
protected:
	std::queue<GenericEvent*> events;

	SerializerType serType;

	ISerializer* serializer;

public:
	IPersistence(SerializerType serType = SerializerType::JSON_SER);
	virtual ~IPersistence();

	virtual void send(GenericEvent* event);

	virtual void flush();
};

