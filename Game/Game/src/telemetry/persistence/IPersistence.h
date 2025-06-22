#pragma once
#include "../DQueue.h"
#include "../serialization/ISerializer.h"

enum SerializerType {
	JSON_SER,
	CSV_SER,
	YAML_SER
};

class IPersistence
{
protected:
	DQueue<GenericEvent*,500> events = DQueue<GenericEvent*, 500>();
	//EventQueue events;

	SerializerType serType;

	ISerializer* serializer;

public:
	IPersistence(SerializerType serType = SerializerType::JSON_SER);
	virtual ~IPersistence();

	virtual void send(GenericEvent* event);

	virtual void flush();
};

