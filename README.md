# 42sh
Le 42sh est un projet qui vise à reproduire un shell en langage C

Fonctionnalitées présentes :

◦Édition complète de la ligne de commande
◦Les opérateurs de redirection et d’aggrégation :
	— >
	— >>
	— <
	— <<
	— >&
	— <&
◦Les pipes|◦Les séparateurs;

Les built-ins suivants :

◦cd
◦echo
◦exit
◦type

La gestion des variables internes au shell (Ne vous occupez pas des variables enlecture-seule).
◦La création de variable interne selon la syntaxe :name=value.
◦L’exportation des variables internes vers l’environnement, via le built-inexport.
◦La possibilité de lister les variables internes du shell via le built-inset(pasd’option requises).
◦Le retrait des variables internes et d’environnement, via le built-inunset(pasd’option requises).
◦La création de variable d’environnement pour une commande unique, exemple :HOME=/tmp cd.
◦L’expansion simple des paramètres selon la syntaxe${}(pas de format sup-plémentaire requis).
◦La gestion des parametres speciaux, comme?pour le code de sortie de lacommande precedente.

Les inhibiteurs”(double quote),’(simple quote) et\(backslash)

La gestion complète de l’historique :

◦La sauvegarde dans un fichier pour être utilisé sur plusieurs sessions
◦Le built-infc(toutes les options POSIX)
◦Recherche incrémentale dans l’historique avec CTRL-R

La gestion desaliasvia les built-insaliasetunalias

Une table de hachage ainsi que le built-inhashpour intéragir avec elle

Le built-intestavec les opérateurs suivants :-b,-c,-d,-e,-f,-g,-L,-p,-r,-S,-s,-u,-w,-x,-z,=,!=,-eq,-ne,-ge,-lt,-le,!. Ainsi que la possibilitéd’un simple opérande, sans opérateur.
