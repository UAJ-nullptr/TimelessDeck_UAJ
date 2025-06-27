import os
import matplotlib.pyplot as plt
import numpy as np
from datetime import datetime

def getCurrentTime():
    return datetime.now().strftime("%H-%M-%S_%d-%m-%Y")

def createFolder():
    folder = f"Graphics_{getCurrentTime()}"
    folder_path = os.path.join("results", folder)
    os.makedirs(folder_path, exist_ok=True)
    return folder_path

def createGraphic(categories, values, graphic_title, image_title, folder):
    colors = plt.cm.viridis(np.linspace(0, 1, len(categories))) 
    plt.bar(categories, values, color=colors)

    plt.title(graphic_title)
    plt.xlabel('Event')
    plt.ylabel('Mean value')

    name = image_title + f"_{getCurrentTime()}.png"
    path = os.path.join(folder, name)
    plt.savefig(path)
    plt.close()
    print("Graphic created and saved in: ", path)

def getEventIndexes():
    return {4, 5, 6, 7, 8, 9, 10, 11, 12, 13}