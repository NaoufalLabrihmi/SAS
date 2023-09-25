#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#define MAX_TACHES 100 // Définir le nombre maximum de tâches
#define MAX_COLLABORATORS 10  // Définir le nombre maximum de collaborateurs par tâche


typedef struct {
    int jour;
    int mois;
    int annee;
} date;
typedef struct {
    char nom[50];      
    char prenom[50];    
    char email[100];    
} collaborateur;
typedef struct {
    int id;
    char *titre;
    char *description;
    char *statut;
    date creation_date;
    date deadline;
    collaborateur collaborateurs[MAX_COLLABORATORS];  // Tableau de collaborateurs
    int nombre_collaborateurs;  // Nombre de collaborateurs affectés à la tâche
} tache;
typedef struct {
    tache *taches; // Tableau dynamique pour stocker les tâches
    int nbr_tache;
    int taille_max; // Taille maximale du tableau dynamique
} LS;

int x = 1; // ID de tâche global, en supposant que vous souhaitiez l'initialiser à 1.

void Initialiser(LS *l) {
    l->nbr_tache = 0;
    l->taille_max = MAX_TACHES;
    l->taches = (tache *)malloc(sizeof(tache) * l->taille_max); // Allouer de la mémoire pour les tâches
}



/* Pour permettre à l'utilisateur de saisir le nombre maximum de tâches.
void Initialiser(LSC *l, int taille) {
    l->nbr_tache = 0;
    l->taille_max = taille;
    l->taches = (tache *)malloc(sizeof(tache) * l->taille_max); // Allocate memory for tasks
}*/
void AjouterCollaborateur(tache *t) {
    printf("Entrez le nombre de collaborateurs pour cette tache : ");
    scanf(" %d", &t->nombre_collaborateurs);

    if (t->nombre_collaborateurs < MAX_COLLABORATORS) {
        for (int i = 0; i < t->nombre_collaborateurs; i++) {
            printf("Entrez le nom du collaborateur : ");
            scanf(" %s", t->collaborateurs[i].nom);
            printf("Entrez le prenom du collaborateur : ");
            scanf(" %s", t->collaborateurs[i].prenom);
            printf("Entrez l'email du collaborateur : ");
            scanf(" %s", t->collaborateurs[i].email);
            printf("Collaborateur ajoute avec succes.\n");
        }
    } else {
        printf("Impossible d'ajouter plus de collaborateurs à cette tache.\n");
    }
}

tache* Creertache() {
    tache *A = (tache*)malloc(sizeof(tache));
    A->titre = (char *)malloc(sizeof(char) * 30);
    A->description = (char *)malloc(sizeof(char) * 500);
    A->statut = (char *)malloc(sizeof(char) * 30);
    A->id = x++;

    time_t current_timestamp;
    time(&current_timestamp);
    struct tm *current_tm = localtime(&current_timestamp);
    A->creation_date.jour = current_tm->tm_mday;
    A->creation_date.mois = current_tm->tm_mon + 1;
    A->creation_date.annee = current_tm->tm_year + 1900;
    A->nombre_collaborateurs = 0;

    printf("Entrez le titre de la tache :\n");
    fflush(stdin);
    gets(A->titre);
    printf("Entrez la description de la tache :\n");
    fgets(A->description, 500, stdin);

    int choix_statut;
    do {
        printf("Choisissez le statut de la tache:\n");
        printf("1. a realiser\n");
        printf("2. En cours de realisation\n");
        printf("3. Finalisee\n");
        printf("Choix: ");
        scanf("%d", &choix_statut);

        switch (choix_statut) {
            case 1:
                strcpy(A->statut, "a realiser");
                break;
            case 2:
                strcpy(A->statut, "En cours de realisation");
                break;
            case 3:
                strcpy(A->statut, "Finalisee");
                break;
            default:
                printf("Choix invalide. Veuillez choisir parmi les options disponibles.\n");
        }
    } while (choix_statut < 1 || choix_statut > 3);

    do {
        printf("Entrez le deadline de la tache (jour/mois/annee) :\n");
        scanf("%d%d%d", &A->deadline.jour, &A->deadline.mois, &A->deadline.annee);
    } while (A->deadline.jour > 31 || A->deadline.jour < 1 || A->deadline.mois > 12 || A->deadline.mois < 1 || A->deadline.annee < 2023);

    AjouterCollaborateur(A);

    return A;
}



void Ajouter_fin(LS *L, tache A) {
    if (L->nbr_tache < MAX_TACHES) {
        L->taches[L->nbr_tache++] = A;
    } else {
        printf("Le tableau est plein. Impossible d'ajouter plus de taches.\n");
    }
}

void AjouterPlusieursTaches(LS *L, int nbr) {
    for (int i = 0; i < nbr; i++) {
        tache *nouvelle_tache = Creertache();
        // Fixe la date de création
        time_t current_time;
        struct tm *tm_info;
        time(&current_time);
        tm_info = localtime(&current_time);
        nouvelle_tache->creation_date.jour = tm_info->tm_mday;
        nouvelle_tache->creation_date.mois = tm_info->tm_mon + 1; // Le mois est basé sur 0
        nouvelle_tache->creation_date.annee = tm_info->tm_year + 1900; // Années depuis 1900
        Ajouter_fin(L, *nouvelle_tache);
    }
}

void ClearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

void AfficherTaches(LS *L) {
    printf("----------------------Liste des taches :------------------------------\n");
    for (int i = 0; i < L->nbr_tache; i++) {
        printf("\t| Tache %d\n", i + 1);
        printf("\t| ID : %d\n", L->taches[i].id);
        printf("\t| Titre : %s\n", L->taches[i].titre);
        L->taches[i].description[strcspn(L->taches[i].description, "\n")] = 0;
        printf("\t| Description : %s\n", L->taches[i].description);
        printf("\t| Statut : %s\n", L->taches[i].statut);
        printf("\t| Deadline : %02d/%02d/%04d\n", L->taches[i].deadline.jour, L->taches[i].deadline.mois, L->taches[i].deadline.annee);
        printf("\t| Date de creation : %02d/%02d/%04d\n", L->taches[i].creation_date.jour, L->taches[i].creation_date.mois, L->taches[i].creation_date.annee);
        if (L->taches[i].nombre_collaborateurs != 0) {
            printf("\t| Collaborateurs : \n");
            for (int j = 0; j < L->taches[i].nombre_collaborateurs; j++) {
                printf("\t|   - Nom : %s\n", L->taches[i].collaborateurs[j].nom);
                printf("\t|     Prenom : %s\n", L->taches[i].collaborateurs[j].prenom);
                printf("\t|     Email : %s\n", L->taches[i].collaborateurs[j].email);
            }
        }
        printf("\n---------------------------------------------------------------------\n");
    }
    
    printf("Appuyez sur une touche pour revenir au menu...");
    ClearInputBuffer(); // Clear the input buffer
    getchar();  // Wait for a key press to continue
}



int CompareTaches(const void *tache1, const void *tache2) {
    const tache *task1 = (const tache *)tache1;
    const tache *task2 = (const tache *)tache2;
    return strcmp(task1->titre, task2->titre);
}

int CompareDeadlines(const void *tache1, const void *tache2) {
    const tache *task1 = (const tache *)tache1;
    const tache *task2 = (const tache *)tache2;
    
    // Comparez d'abord par année, puis par mois et enfin par jour.
    if (task1->deadline.annee != task2->deadline.annee) {
        return task1->deadline.annee - task2->deadline.annee;
    }
    if (task1->deadline.mois != task2->deadline.mois) {
        return task1->deadline.mois - task2->deadline.mois;
    }
    return task1->deadline.jour - task2->deadline.jour;
}


void TrierTachesAlphabetiquement(LS *L) {
// Trier les tâches par ordre alphabétique en fonction de leurs titres 
   qsort(L->taches, L->nbr_tache, sizeof(tache), CompareTaches);
}

void TrierTachesParDeadline(LS *L) {
    // Trier les tâches en fonction de leurs délais
    qsort(L->taches, L->nbr_tache, sizeof(tache), CompareDeadlines);
}


void LibererMemoire(LS *L) {
    for (int i = 0; i < L->nbr_tache; i++) {
        free(L->taches[i].titre);
        free(L->taches[i].description);
        free(L->taches[i].statut);
    }
}


// Fonction pour créer une structure tm à partir d'une structure date
struct tm date_to_tm(date d) {
    struct tm tm_date = {0};
    tm_date.tm_year = d.annee - 1900;  
    tm_date.tm_mon = d.mois - 1;        
    tm_date.tm_mday = d.jour;           
    return tm_date;
}

// Fonction d'affichage des tâches avec une date limite dans les 3 jours ou moins
void AfficherTachesProches(LS *L) {
    if (L->nbr_tache == 0) {
        printf("La liste est vide !!\n");
        return; 
    }

    time_t current_timestamp;
    time(&current_timestamp);

    int found = 0; // Pour savoir si au moins une tâche a été trouvée

    printf("Tâches dont le deadline est dans 3 jours ou moins :\n");
    for (int i = 0; i < L->nbr_tache; i++) {
        struct tm deadline_tm = date_to_tm(L->taches[i].deadline);
        time_t deadline_timestamp = mktime(&deadline_tm);
        
        double difference = difftime(deadline_timestamp, current_timestamp) / (60 * 60 * 24); // La différence en jours
        if (difference >= 0 && difference <= 3) {
            printf("Identifiant: %d, Titre: %s, Deadline: %02d/%02d/%04d\n",
                   L->taches[i].id, L->taches[i].titre,
                   L->taches[i].deadline.jour, L->taches[i].deadline.mois, L->taches[i].deadline.annee);
            found = 1; // Marque qu'au moins une tâche a été trouvée
        }
    }

    if (!found) {
        printf("Aucune tache dont le deadline est dans 3 jours ou moins n'a ete trouvee.\n");
    }
}

// Fonction pour modifier la description d'une tâche.
void ModifierDescription(LS *L) {
    if (L->nbr_tache == 0) {
        printf("La liste est vide !!\n");
        return; 
    }

    int id;
    printf("Entrez l'identifiant de la tache que vous souhaitez modifier :\n");
    scanf("%d", &id);

    int found = 0; // Pour savoir si la tâche avec l'ID spécifié est trouvée.

    for (int i = 0; i < L->nbr_tache; i++) {
        if (L->taches[i].id == id) {
            printf("Entrez la nouvelle description pour la tache %d :\n", id);
            getchar(); // Consomme le caractère de nouvelle ligne laissé dans le tampon
            fgets(L->taches[i].description, 500, stdin); 
            found = 1;
            printf("Description de la tache %d modifiee avec succes.\n", id);
            break; 
        }
    }
    if (!found) {
        printf("Aucune tache avec l'identifiant %d n'a ete trouvee.\n", id);
    }
}

// Fonction pour modifier le statut d'une tâche.
void ModifierStatut(LS *L) {
    if (L->nbr_tache == 0) {
        printf("La liste est vide !!\n");
        return;
    }
    int id,choix_statut;
    printf("Entrez l'identifiant de la tache que vous souhaitez modifier :\n");
    scanf("%d", &id);

    int found = 0; // Pour savoir si la tâche avec l'ID spécifié est trouvée

    for (int i = 0; i < L->nbr_tache; i++){
    if (L->taches[i].id == id){
    do {
        printf("Choisissez le nouveau statut pour la tâche %d :\n");
        printf("1.a realiser\n");
        printf("2.En cours de realisation\n");
        printf("3.Finalisee\n");
        printf("Choix: ");
        scanf("%d", &choix_statut);

        switch (choix_statut) { 
            case 1:
                strcpy(L->taches[i].statut, "A realiser");
                break;
            case 2:
                strcpy(L->taches[i].statut, "En cours de realisation");
                break;
            case 3:
                strcpy(L->taches[i].statut, "Finalisee");
                break;
            default:
                printf("Choix invalide. Veuillez choisir parmi les options disponibles.\n");
        }
    } while (choix_statut < 1 || choix_statut > 3);
    found = 1;
    printf("Statut de la tache %d modifie avec succes.\n", id);
    break;
    }
   }
    if (!found) {
        printf("Aucune tache avec l'identifiant %d n'a ete trouvee.\n", id);
    }
}

// Fonction pour modifier la date limite d'une tâche
void ModifierDeadline(LS *L) {
    if (L->nbr_tache == 0) {
        printf("La liste est vide !!\n");
        return;
    }

    int id;
    printf("Entrez l'identifiant de la tache dont vous souhaitez modifier la deadline :\n");
    scanf("%d", &id);

    int found = 0;

    for (int i = 0; i < L->nbr_tache; i++) {
        if (L->taches[i].id == id) {
            printf("Entrez la nouvelle deadline pour la tache %d (jour/mois/annee) :\n", id);
            scanf("%d%d%d", &L->taches[i].deadline.jour, &L->taches[i].deadline.mois, &L->taches[i].deadline.annee);
            found = 1;
            printf("Deadline de la tache %d modifiée avec succes.\n", id);
            break;
        }
    }
    if (!found) {
        printf("Aucune tache avec l'identifiant %d n'a ete trouvee.\n", id);
    }
}

// Fonction pour supprimer une tâche par son identifiant
void SupprimerTacheParIdentifiant(LS *L) {
    if (L->nbr_tache == 0) {
        printf("La liste est vide !!\n");
        return;
    }

    int id;
    printf("Entrez l'identifiant de la tache que vous souhaitez supprimer :\n");
    scanf("%d", &id);

    int found = 0; 

    for (int i = 0; i < L->nbr_tache; i++) {
        if (L->taches[i].id == id) {
            // Décaler les tâches restantes pour combler le vide
            for (int j = i; j < L->nbr_tache - 1; j++) {
                L->taches[j] = L->taches[j + 1];
            }
            L->nbr_tache--;
            found = 1;
            printf("Tache avec l'identifiant %d supprimee avec succes.\n", id);
            break; 
        }
    }

    if (!found) {
        printf("Aucune tache avec l'identifiant %d n'a ete trouvee.\n", id);
    }
}

// Fonction pour rechercher une tâche par son identifiant (ID)
void RechercherTacheParIdentifiant(const LS *L, int id) {
    if (L->nbr_tache == 0) {
        printf("La liste est vide !!\n");
        return; 
    }

    int trouve = 0; 

    for (int i = 0; i < L->nbr_tache; i++) {
        if (L->taches[i].id == id) {
        printf("Tache trouvee par identifiant :\n");
        printf("\t| ID : %d\n", L->taches[i].id);
        printf("\t| Titre : %s\n", L->taches[i].titre);
        L->taches[i].description[strcspn(L->taches[i].description, "\n")] = 0;
        printf("\t| Description : %s\n", L->taches[i].description);
        printf("\t| Statut : %s\n", L->taches[i].statut);
        printf("\t| Deadline : %02d/%02d/%04d\n", L->taches[i].deadline.jour, L->taches[i].deadline.mois, L->taches[i].deadline.annee);
        printf("\t| Date de creation : %02d/%02d/%04d\n", L->taches[i].creation_date.jour, L->taches[i].creation_date.mois, L->taches[i].creation_date.annee);
        trouve=1;
            break; 
        }
    }

    if (!trouve) {
        printf("Aucune tache avec l'identifiant %d n'a ete trouvee.\n", id);
    }
}



// Fonction pour rechercher une tâche par son titre
void RechercherTacheParTitre(const LS *L, const char *titre) {
    if (L->nbr_tache == 0) {
        printf("La liste est vide !!\n");
        return; 
    }
    int found = 0; 
    for (int i = 0; i < L->nbr_tache; i++) {
        if (strcmp(L->taches[i].titre, titre) == 0) {
        printf("Tache trouvee par titre :\n");
        printf("\t| ID : %d\n", L->taches[i].id);
        printf("\t| Titre : %s\n", L->taches[i].titre);
        L->taches[i].description[strcspn(L->taches[i].description, "\n")] = 0;
        printf("\t| Description : %s\n", L->taches[i].description);
        printf("\t| Statut : %s\n", L->taches[i].statut);
        printf("\t| Deadline : %02d/%02d/%04d\n", L->taches[i].deadline.jour, L->taches[i].deadline.mois, L->taches[i].deadline.annee);
        printf("\t| Date de creation : %02d/%02d/%04d\n", L->taches[i].creation_date.jour, L->taches[i].creation_date.mois, L->taches[i].creation_date.annee);
            found = 1;
        }
    }
    if (!found) {
        printf("Aucune tache avec le titre '%s' n'a ete trouvee.\n", titre);
    }
}

// Fonction pour calculer le nombre de jours restant avant une date limite
int DaysUntilDeadline(date deadline) {
    struct tm deadline_tm = {0};
    deadline_tm.tm_year = deadline.annee - 1900; 
    deadline_tm.tm_mon = deadline.mois - 1;        
    deadline_tm.tm_mday = deadline.jour;           

    time_t current_timestamp;
    time(&current_timestamp);
    struct tm *current_tm = localtime(&current_timestamp);

    deadline_tm.tm_hour = 0;
    deadline_tm.tm_min = 0;
    deadline_tm.tm_sec = 0;

    time_t deadline_timestamp = mktime(&deadline_tm);
    double difference = difftime(deadline_timestamp, mktime(current_tm)) / (60 * 60 * 24); 

    return (int)difference;
}

// Fonction pour effectuer des statistiques sur les tâches
void FaireDesStatistiques(const LS *L) {
    if (L->nbr_tache == 0) {
        printf("La liste est vide !!\n");
        return; 
    }

    int total_tasks = L->nbr_tache;
    int completed_tasks = 0;
    int incomplete_tasks = 0;

    printf("*******Statistiques des taches :*******\n");
    printf("\n\tNombre total des taches : %d\n", total_tasks);
    
    for (int i = 0; i < L->nbr_tache; i++) {
        if (strcmp(L->taches[i].statut, "Finalisee") == 0) {
            completed_tasks++;
        } else {
            incomplete_tasks++;
        }

        int days_remaining = DaysUntilDeadline(L->taches[i].deadline);
        printf("\n -->Tache %d\n", L->taches[i].id);
        printf("    Titre: %s\n",L->taches[i].titre);
        printf("    Statut : %s\n", L->taches[i].statut);
        printf("    Deadline : %02d/%02d/%04d\n", L->taches[i].deadline.jour, L->taches[i].deadline.mois, L->taches[i].deadline.annee);
        printf("    Jours restants jusqu'au delai : %d\n", days_remaining);
    }
    printf("\n        Nombre des taches completes : %d\n", completed_tasks);
    printf("        Nombre des taches incompletes : %d\n", incomplete_tasks);    

}
void clearScreen() {
    system("cls");
}

// Fonction pour rechercher une tâche par son statut
void RechercherTacheParStatut(const LS *L) {
    if (L->nbr_tache == 0) {
        printf("La liste est vide !!\n");
        return; 
    }
    
    int choix_statut;
    const char *statut;
    
    printf("Choisissez le statut de la tache:\n");
    printf("1. A realiser\n");
    printf("2. En cours de realisation\n");
    printf("3. Finalisee\n");
    printf("Choix: ");
    scanf("%d", &choix_statut);
    
    switch (choix_statut) {
        case 1:
            statut = "a realiser";
            break;
        case 2:
            statut = "En cours de realisation";
            break;
        case 3:
            statut = "Finalisee";
            break;
        default:
            printf("Choix invalide.\n");
            return;
    }

    int found = 0; 
    for (int i = 0; i < L->nbr_tache; i++) {
        if (strcmp(L->taches[i].statut, statut) == 0) {
            printf("Tache trouvee par statut :\n");
            printf("\t| ID : %d\n", L->taches[i].id);
            printf("\t| Titre : %s\n", L->taches[i].titre);
            L->taches[i].description[strcspn(L->taches[i].description, "\n")] = 0;
            printf("\t| Description : %s\n", L->taches[i].description);
            printf("\t| Statut : %s\n", L->taches[i].statut);
            printf("\t| Deadline : %02d/%02d/%04d\n", L->taches[i].deadline.jour, L->taches[i].deadline.mois, L->taches[i].deadline.annee);
            printf("\t| Date de creation : %02d/%02d/%04d\n", L->taches[i].creation_date.jour, L->taches[i].creation_date.mois, L->taches[i].creation_date.annee);
            found = 1;
        }
    }
    
    if (!found) {
        printf("Aucune tache avec le statut '%s' n'a ete trouvee.\n", statut);
    }
}


int main() {
	/* Pour permettre à l'utilisateur de saisir le nombre maximum de tâches. 
	int taille;
    printf("Entrez le nombre maximum de tâches (taille) : ");
    scanf("%d", &taille);
    LSC liste_taches;
    Initialiser(&liste_taches, taille);*/
    LS liste_taches;
    Initialiser(&liste_taches);

    int nbr_taches;
    int choix;
	returning:
    do {
    	clearScreen();
        printf("\n-----------------------------Menu de gestion des taches :-----------------------------\n");
        printf("\n\t1. Ajouter des taches\n");
        printf("\t2. Modifier la description d'une tache\n");
        printf("\t3. Modifier le statut d'une tache\n");
        printf("\t4. Modifier le deadline d'une tache\n");
        printf("\t5. Supprimer une tache par identifiant\n");
        printf("\t6. Rechercher une tache par identifiant\n");
        printf("\t7. Rechercher une tache par titre\n");
        printf("\t8. Recherche une tache par statut\n");
        printf("\t9. Afficher les taches\n");
        printf("\t10. Afficher les taches dont le deadline est dans 3 jours ou moins\n");
        printf("\t11. Trier les taches par titre\n"); // Added option to sort by title
        printf("\t12. Trier les taches par deadline\n"); // Added option to sort by deadline
        printf("\t13. Statistiques des taches\n");
        printf("\t14. Quitter le programme\n");
        printf("\n\tEntrez votre choix : ");
        scanf("%d", &choix);
		
        switch (choix) {
                case 1:
        	printf("Combien de taches voulez-vous ajouter ?\n");
  			scanf("%d", &nbr_taches);
  			AjouterPlusieursTaches(&liste_taches, nbr_taches);
                break;
			  case 2:
                ModifierDescription(&liste_taches);
                break;
            case 3:
                ModifierStatut(&liste_taches);
                break;
            case 4:
                ModifierDeadline(&liste_taches);
                break;
            case 5:
                SupprimerTacheParIdentifiant(&liste_taches);
                break;
            case 6:
                printf("Entrez l'identifiant de la tache que vous souhaitez rechercher :\n");
                int id;
                scanf("%d", &id);
                RechercherTacheParIdentifiant(&liste_taches, id);
                break;
            case 7:
                printf("Entrez le titre de la tache que vous souhaitez rechercher :\n");
                char titre[30];
                getchar(); // Consume the newline character left in the buffer
                fgets(titre, sizeof(titre), stdin);
                titre[strcspn(titre, "\n")] = 0; // Supprime le caractère de nouvelle ligne
                RechercherTacheParTitre(&liste_taches, titre);
                break;
			case 8:
			RechercherTacheParStatut(&liste_taches);
    			break;

            case 9:
                AfficherTaches(&liste_taches);
                break;
            case 10:
                AfficherTachesProches(&liste_taches);
                break;
            case 11:
                TrierTachesAlphabetiquement(&liste_taches); 
                printf("Taches triees par titre.\n");
                AfficherTaches(&liste_taches);
                break;
			case 12:
			    TrierTachesParDeadline(&liste_taches); 
			    printf("Taches triees par deadline.\n");
			    AfficherTaches(&liste_taches);
				goto returning;
    		break;
            case 13:
                FaireDesStatistiques(&liste_taches);
                break;
			case 14:
                printf("Fin du programme.\n");
                exit(0);
                break;
            default:
                printf("Choix invalide. Veuillez entrer un choix valide.\n");
                break;
        }getch();
    } while (choix != 12);

    LibererMemoire(&liste_taches); // Free allocated memory

    return 0;
}
