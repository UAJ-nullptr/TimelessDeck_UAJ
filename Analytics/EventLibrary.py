import json
import os

# Map of values of eType attribute
# {
#   0: 'START_SESSION', 
#   1:'END_SESSION', 
#   2:'START_LEVEL', 
#   3:'END_LEVEL', 
#   4:'CARD_CHANGED',
#   5:'ABILITY_USED', 
#   6:'PLAYER_HEALED', 
#   7:'MANA_TAKEN', 
#   8:'NOT_ENOUGHT_MANA', 
#   9:'LEVEL_EXIT_POSSIBLE',
#   10:'LEAVE_FAILED', 
#   11:'MOVED_FROM_HAND', 
#   12:'MOVED_TO_HAND', 
#   13:'INVENTORY_LEFT'
# }

class EventLibrary :
    # Lista de listas de eventos ([0]= {eventos de tipo 0}, [1] = {eventos de tipo 1}, etc)
    events = []

    def __init__(self, folder, numEvents):
        self.createList(numEvents)
        self.loadEvents(folder)
        self.sortEvents()

    # Función para asegurar que la lista tiene suficientes sublistas
    def createList(self, numEvents):
        for i in range(numEvents):
            self.events.append([])

    def loadEvents(self, folder):
        # Leer todos los archivos .json en la carpeta
        for file in os.listdir(folder):
            if file.endswith('.json'):
                path = os.path.join(folder, file)
                with open(path, 'r', encoding='utf-8') as archivo:
                    try:
                        data = json.load(archivo)
                        data = self.isValidSessionFile(data, file)
                        for obj in data:
                            event_type = obj.get('eType')
                            if isinstance(event_type, int):  # solo si eventType es un entero válido
                                self.events[event_type].append(obj)
                    except json.JSONDecodeError:
                        print(f"Error al leer {file}, JSON inválido.")

    def isValidSessionFile(self, data, file_name=""):
        sorted_data = sorted(data, key=lambda x: x.get('timeStamp'))
        start_session_events = []
        end_session_events = []

        for obj in sorted_data:
            if obj.get('eType') == 0:
                start_session_events.append(obj)
            elif obj.get('eType') == 1:
                end_session_events.append(obj)

        # Si no hay los mismos eventos de inicio de sesion que de fin de sesion el archivo no es valido
        if len(start_session_events) != len(end_session_events):
            print(f"Desajuste de sesiones encontrado en el archivo [{file_name}]. Archivo ignorado.")
            return {}
        
        return self.checkLevelErrors(data)

    def checkLevelErrors(self, data):
        limit_events = [(i, e) for i, e in enumerate(data) if e.get('eType') in (2, 3)]
        if len(limit_events) == 0:
            return {}
        start_events_stack = []
        ranges_to_erase = []

        for index, event in limit_events:
            eType = event['eType']
            if eType == 2:
                start_events_stack.append((index, event))
            elif eType == 3:
                if (start_events_stack):
                    start_index, start_event = start_events_stack.pop()
                    # Verificar que ambos tengan levelId y sean iguales
                    # if start_event.get('levelId') != event.get('levelId'):
                    #     ranges_to_erase.append((start_index, index))
                    if start_event['timeStamp'] >= event['timeStamp']:
                        ranges_to_erase.append((start_index, index))
                else:
                    # end_level sin start_level → borrar desde el inicio hasta su indice
                    ranges_to_erase.append((0, index))

        # Si quedan start_levels sin cerrar
        for start_index, start_event in start_events_stack:
            next_start_index = None
            for index in range(start_index + 1, len(data)):
                if data[index].get('eType') == 2:
                    next_start_index = index
                    break
            end_index = next_start_index if next_start_index is not None else len(data)
            ranges_to_erase.append((start_index, end_index))

        # Indices a eliminar
        indices_a_eliminar = set()
        for start, end in ranges_to_erase:
            indices_a_eliminar.update(range(start, end + 1))

        # Eliminar todos los eventos no validos
        data = [e for i, e in enumerate(data) if i not in indices_a_eliminar]
        if indices_a_eliminar :
            print(f"Eliminados {len(indices_a_eliminar)} eventos fuera de rangos válidos.")

        return data
 
    def sortEvents(self):
        for eventList in self.events:
            eventList.sort(key=lambda x: x.get('timeStamp'))

    def getLibrary(self):
        return self.events
    
    def getEventList(self, eventType):
        try: 
            return self.events[eventType]
        except IndexError:
            print(f"Error: No hay eventos con eventType = {eventType}. El índice está fuera del rango.")