# ✅ Check-list Minishell : Tokenisation + Analyse syntaxique

---

## 🔹 I. Tokenisation (Lexer)

### 🔸 Lecture et préparation
- [ ] Lire la ligne d'entrée (`readline`)
- [ ] Sauter les espaces inutiles (hors quotes)
- [ ] Initialiser une structure de token (`t_token`)
- [ ] Garder les quotes pour traitement interne

### 🔸 Quotes
- [ ] Gérer les quotes simples `'...'` (pas d’expansion)
- [ ] Gérer les quotes doubles `"..."` (expansion possible)
- [ ] Détecter les quotes non fermées (erreur de syntaxe)

### 🔸 Caractères spéciaux
- [ ] Détecter : `|`, `<`, `>`, `<<`, `>>`
- [ ] Couper les tokens correctement
- [ ] Ne pas confondre `>>>`, `><`, etc. (erreurs)

### 🔸 Expansion `$`
- [ ] Expansion `$VAR`, `$?`
- [ ] Pas d’expansion dans quotes simples `'...'`
- [ ] Expansion autorisée dans `"..."` ou sans quotes
- [ ] Variables inexistantes → remplacées par chaîne vide

### 🔸 Construction des tokens
- [ ] Créer un token pour chaque mot ou symbole
- [ ] Attribuer le bon type (`WORD`, `PIPE`, `REDIR_IN`, etc.)
- [ ] Ajouter à une liste chaînée (ou tableau dynamique)

---

## 🔹 II. Analyse syntaxique (Parser)

### 🔸 Général
- [ ] Parcourir les tokens en séquence
- [ ] Identifier les blocs de commande séparés par `|`

### 🔸 Vérifications syntaxiques
- [ ] Pas de pipe seul au début ou à la fin
- [ ] Pas de redirection sans mot derrière
- [ ] Pas de doubles pipes (`||`) ou redirections invalides
- [ ] Redirections bien formées : `> fichier`, `<< limiter`, etc.

### 🔸 Commandes
- [ ] Chaque bloc doit contenir au moins une commande (`WORD`)
- [ ] Extraire tous les arguments associés

### 🔸 Redirections
- [ ] `>` → fichier de sortie (truncate)
- [ ] `>>` → fichier de sortie (append)
- [ ] `<` → fichier d’entrée
- [ ] `<<` → heredoc avec gestion des quotes dans le délimiteur

### 🔸 Heredoc
- [ ] Lire jusqu’au délimiteur spécifié
- [ ] Ne pas faire d’expansion si délimiteur entre quotes
- [ ] Stocker temporairement le contenu

---

## 🔹 III. Construction de la structure d'exécution

- [ ] Une structure `t_command` par commande
- [ ] Contient : `argv`, fichiers de redirection, flags heredoc/append
- [ ] Chaînage avec `next` pour les pipes

```c
typedef struct s_command {
    char **argv;
    char *infile;
    char *outfile;
    int append;
    int heredoc;
    struct s_command *next;
} t_command;
