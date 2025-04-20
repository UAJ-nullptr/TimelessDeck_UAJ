import pandas as pd
import os


class Loader:



    def __init__(self, filepath, loadMultipleFiles = False):

        self.loadFiles(filepath, loadMultipleFiles)


    def loadFiles(self, filepath, loadMultipleFiles):
        self.data = pd.DataFrame()
        if (loadMultipleFiles):
            for file in os.listdir(filepath):
                if file.endswith('.json'):
                    file_path = os.path.join(filepath, file)
                    self.data = pd.concat([self.data, pd.read_json(file_path)], ignore_index=True)
            pass
        else:
            self.data = pd.read_json(filepath)
            pass
