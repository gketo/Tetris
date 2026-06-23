#!/bin/bash

# Fonction pour afficher le contenu d'un dossier de manière hiérarchique
function list_dir() {
    local dir="$1"
    local indent="$2"

    # Vérifie si le dossier existe
    if [ ! -d "$dir" ]; then
        echo "${indent}[Dossier manquant] $dir"
        return
    fi

    # Liste les fichiers et dossiers
    for entry in "$dir"/*; do
        if [ -d "$entry" ]; then
            echo "${indent}📁 $(basename "$entry")"
            list_dir "$entry" "  $indent"  # appel récursif pour les sous-dossiers
        elif [ -f "$entry" ]; then
            echo "${indent}📄 $(basename "$entry")"
        fi
    done
}

# Parcours des dossiers App et Core
echo "Structure du dossier ./App:"
list_dir "./App" "  "

echo ""
echo "Structure du dossier ./Core:"
list_dir "./Core" "  "