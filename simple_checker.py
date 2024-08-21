import subprocess
import pandas as pd

# Fichiers d'entrée et de sortie
input_file = 'Test.xlsx'
output_file = 'output_results.xlsx'

def execute_test(test_command):
    try:
        # Exécuter Minishell directement
        process = subprocess.Popen('./minishell', stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        
        # Envoyer la commande à minishell et quitter
        stdout, stderr = process.communicate(input=f'{test_command}\nexit\n')

        # Extraire la sortie de minishell et les erreurs
        minishell_output = stdout.strip()
        error_output = stderr.strip()

        return minishell_output, error_output

    except Exception as e:
        return f"Erreur : {str(e)}", ""

def process_tests():
    # Lire les tests depuis le fichier Excel
    df = pd.read_excel(input_file)
    
    # Liste pour stocker les résultats
    results = []

    # Pour chaque ligne dans le fichier Excel, exécuter le test
    for index, row in df.iterrows():
        test_command = row['Test']
        result, error = execute_test(test_command)
        
        # Ajouter les résultats à la liste
        results.append({
            'Test': f"Test {index + 1}/{len(df)}: {test_command}",
            'Minishell Result': result,
            'Error Output': error
        })

    # Créer un DataFrame avec les résultats
    results_df = pd.DataFrame(results)

    # Écrire le DataFrame dans un fichier Excel
    results_df.to_excel(output_file, index=False)

if __name__ == "__main__":
    process_tests()
