#import subprocess
import pandas as pd

# Fichiers d'entrée et de sortie
input_file = 'tests_variable.xlsx'
output_file = 'output_results.xlsx'
temp_file_name = 'valgrind_output.log'  # Nom du fichier temporaire à la racine du répertoire de travail

# Commande Valgrind avec suppressions et vérification des fuites
valgrind_command = ['valgrind', '--suppressions=suppressionsleak.supp', '--leak-check=full', './minishell']

def execute_test(test_command):
    try:
        # Démarrer Valgrind avec Minishell, rediriger stderr vers le fichier temporaire
        valgrind_command_with_redirection = ' '.join(valgrind_command) + f' 2> {temp_file_name}'
        process = subprocess.Popen(valgrind_command_with_redirection, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True, text=True)
        
        # Envoyer la commande à minishell et quitter
        stdout, _ = process.communicate(input=f'{test_command}\nexit\n')

        # Lire la sortie de Valgrind à partir du fichier de log
        with open(temp_file_name, 'r', encoding='utf-8') as temp_file:
            valgrind_output = temp_file.read()

        # Extraire la sortie de minishell
        minishell_output = stdout.strip()

        return minishell_output, valgrind_output

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
        result, leak = execute_test(test_command)
        
        # Ajouter les résultats à la liste
        results.append({
            'Test': f"Test {index + 1}/{len(df)}: {test_command}",
            'Minishell Result': result,
            'Valgrind Output': leak
        })

    # Créer un DataFrame avec les résultats
    results_df = pd.DataFrame(results)

    # Écrire le DataFrame dans un fichier Excel
    results_df.to_excel(output_file, index=False)

if __name__ == "__main__":
    process_tests()
