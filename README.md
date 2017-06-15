# BIRDTOWN
Game created for the C++ lessons - Télécom SudParis (Evry, France)

BOUTANT Thomas
CHARRUAULT Marie


Pour lancer le jeu, être en mode "Release" et non "Debug".


//*****************    CONFIGURATION  *****************//


Dans C:\Software, il y a les fichiers :

	- SFML-2.4.2 

	- tmxlite    //que vous pouvez trouvez ici : https://github.com/fallahn/tmxlite/tree/master/tmxlite
 
 	- pugixml-1.8

Dans Propriétés du projet BirdTown :

	- Pour "C/C++" -> "Autres répertoires Include", il y a : 

			C:\Software\tmxlite\tmxlite\include;
			C:\Software\SFML-2.4.2\include; 
			C:\Software\pugixml-1.8\src


	- Pour "Editeurs de liens" -> "Général" -> "Répertoires de bibliotheques supplémentaires", il y a :

			C:\Software\SFML-2.4.2\lib;
			C:\Software\tmxlite\tmxlite\bin\ReleaseShared;


	Remarque : il faudra peut-être faire un cmake pour obtenir le fichier /bin de tmxlite...


	- Dans "Editeurs de liens" -> "entrée" -> "Dépendances supplémentaires", il y a :

			libtmxlite.lib; sfml-audio.lib;sfml-graphics.lib;sfml-network.lib;sfml-system.lib;sfml-window.lib;kernel32.lib;user32.lib;gdi32.lib;winspool.lib;comdlg32.lib;advapi32.lib;shell32.lib;ole32.lib;oleaut32.lib;uuid.lib;odbc32.lib;odbccp32.lib;%(AdditionalDependencies)

Penser à mettre les fichiers .dll, .pdb, .iobj, .exp dans le dossier Release/ (qui sont aux emplacements cités ci-dessus dans "Répertoires de bibliotheques supplémentaires")





