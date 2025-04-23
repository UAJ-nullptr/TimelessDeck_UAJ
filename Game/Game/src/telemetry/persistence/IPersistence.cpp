#include "IPersistence.h"
#include "../serialization/JSONSerializer.h"
#include "../serialization/CSVSerializer.h"
#include "../serialization/YALMSerializer.h"

IPersistence::IPersistence(SerializerType serType) : serType(serType)
{
	switch (serType)
	{
	case JSON_SER:
		serializer = new JSONSerializer();
		break;
	case CSV_SER:
		// Debido a la complejidad de nuestros eventos, no es eficiente implementar CSV como serializacion alternativa,
		// por lo que se ha añadido la clase pero no se ha implementado su funcionalidad en los eventos ni se hace uso
		// de ella
		//serializer = new CSVSerializer();
		break;
	case YALM_SER:
		serializer = new YALMSerializer();
		break;
	default:
		serializer = new JSONSerializer();
		break;
	}
}

IPersistence::~IPersistence()
{
	delete serializer;
}

void IPersistence::send(GenericEvent* event)
{
	events.push(event);
}

void IPersistence::flush()
{

}
