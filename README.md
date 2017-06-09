# BIRDTOWN
Game created for the C++ lessons - Télécom SudParis (Evry, France)


Pour lancer le jeu, être en mode "Release" et non "Debug".


//*****************    CONFIGURATION  *****************//


Dans C:\Software, il y a les fichiers :
	- SFML-2.4.2
	- tmxlite
	- sfeMovie


Dans Propriétés du projet BirdTown :

	- Pour "C/C++" -> "Autres répertoires Include", il y a : 

			C:\Software\tmxlite\tmxlite\include; C:\Software\SFML-2.4.2\include; C:\Software\sfeMovie\include


	- Pour "Editeurs de liens" -> "Général" -> "Répertoires de bibliotheques supplémentaires", il y a :

			C:\Software\SFML-2.4.2\lib; C:\Software\tmxlite\tmxlite\bin\ReleaseShared; C:\Software\sfeMovie\lib


	- Dans "Editeurs de liens" -> "entrée" -> "Dépendances supplémentaires", il y a :

			libtmxlite.lib; sfml-audio.lib;sfml-graphics.lib;sfml-network.lib;sfml-system.lib;sfml-window.lib;kernel32.lib;user32.lib;gdi32.lib;winspool.lib;comdlg32.lib;advapi32.lib;shell32.lib;ole32.lib;oleaut32.lib;uuid.lib;odbc32.lib;odbccp32.lib;%(AdditionalDependencies)

Penser à mettre les fichiers .dll, .pdb, .iobj, .exp dans le dossier Release/ (qui sont aux emplacements cités ci-dessus dans "Répertoires de bibliotheques supplémentaires")





