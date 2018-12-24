/*
 ============================================================================
 Name        : Tlookup.c
 Author      : Robert Beaudenon
 ID          : 260725065
 Description : Tlookup for Lastnames in the list then print its record
 ============================================================================
 */

#define MAXRECORDS 100
#define MAXNAMELENGTH 15
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Define structure to hold student data
struct StudentRecord
{
	char FirstNames[MAXNAMELENGTH];           //members of the structure of different data types of different size (for the arrays) predefined in the head
	char LastNames[MAXNAMELENGTH];            // the two char variables represents the first and last names of the list with size 15
	int IDNums;                               //The IDs and marks are related to those names
	int Marks;

	struct StudentRecord *left;              //the left child of the tree
	struct StudentRecord *right;             //the right child of the tree
};


//addnode function that implement the data in the binary tree

void addnode(struct StudentRecord** root, struct StudentRecord data){  //input correspond now to a struct

	if((*root) == NULL){                                                                         //if condition to see if root was initialized to NULL


		struct StudentRecord* newRoot=(struct StudentRecord*)malloc(sizeof(struct StudentRecord));  //allocate memory dynamically to the pointer newRoot part of the structure
		//(*root).LastNames = data.LastNames;
		*newRoot = data;                                              //dereference newRoot and store the content of data in it
		*root=newRoot;                                                //dereference root  and store newRoot in it
		(*root)->left=0;                                              //Initializing to 0
		(*root)->right=0;
	}
	/*recursive call*/
	else if (strcmp(data.LastNames , (*root)->LastNames)<0){
		addnode( &((*root)->left) , data);

	}
	else{
		addnode( &((*root)->right) , data);
	}
}




// ptree function that store the adresses of each element of the sorted  binary tree in an array of pointers pointerSRecords

void ptree(struct StudentRecord *root,struct StudentRecord *pointerSRecords[],int *count){

	if(root !=0){
		{
			ptree(root->left,pointerSRecords,&(*count));    //left side of the tree
		}

		pointerSRecords[*count]= &(*root); //instead of printing the in order nodes, we store the corresponding pointers in an array pointerSRecords

		(*count) +=1;                     //incrementation of our counter

		ptree(root->right,pointerSRecords,&(*count));  //right side of the tree
	}

}


// binary search function

int binary_search(struct StudentRecord **pointerSRecords, char *lastname, int numrecords){    // binary search which aim is to search in the list the LastName entered and find it's records
	unsigned int L=0 ;                           //L is initialized at 0 because the array starts at position 0               //same version of the binary search used in the slides but adapted to the assignment , the difference between the two is that there they are using arrays and here we use character strings
	unsigned int R=numrecords;                                          //R take the value of the array length
	unsigned int Middle;                                                     //middle value
	while (L<R){
		Middle=(L+R-1)/2;
		if(strcasecmp(lastname,pointerSRecords[Middle]->LastNames)==0){          //if condition: if the Lastname correspond to the one entered
			return Middle;                                                  // strcasecmp  is insensitive
		}
		else if (strcasecmp(lastname,pointerSRecords[Middle]->LastNames)<0){      //else continue searching using the string comparison in the first half
			R=Middle;
		}else                                                          //else continue searching using the string comparison in the second half
			L=Middle+1 ;
	}
	return -1;                              //return -1 if the LastName was not found in the list
}


//main function

int main(int argc, char * argv[]) {                          //the program will contain 3 arguments argv[1] corresponding to a text file containing names and student IDs
	//argv[2] correspond to a text file containing the marks , and argv[3] which is the search key , which is a string corresponding to the last name of the student

	struct StudentRecord data; struct StudentRecord* root=NULL;  //pointer root initialized to NULL , structure data that will contain the records from the files



	//Read in Names and ID data
	FILE * NamesIDsDataFile,* MarksDataFile;
	if((NamesIDsDataFile = fopen(argv[1], "r")) == NULL || (MarksDataFile = fopen(argv[2], "r")) == NULL){//opening both files and reading them at the same time , the informations are stored into data
		printf("Can't read from file %s , %s \n", argv[1], argv[2]);
		exit(1);
	}


	int numrecords=0;                        //numrecords initialized to 0 will be incremented through each iteration and will give the size
	while (fscanf(NamesIDsDataFile,"%s%s%d",&(data.FirstNames[0]),
			&(data.LastNames[0]), &(data.IDNums)) != EOF && fscanf(MarksDataFile,"%d",&(data.Marks)) != EOF) {
		numrecords++;
		addnode(&root,data);   //once we read lastname , firstname , marks and id into a StudentRecor struct we pass that struct to addnode

	}

	fclose(NamesIDsDataFile);      //closing the two files
	fclose(MarksDataFile);



	struct StudentRecord **pointerSRecords=(struct StudentRecord **)malloc(numrecords*sizeof(struct StudentRecord **)); //allocate memory dynamically to  the array pointerSRecords that will hold the addresses of the sorted tree

	int count =0;                         //initialization of the counter set up to 0
	ptree(root,pointerSRecords,&count);   //calling the function ptree, taking 3 arguments


	int  ResultOfThebinarySearch= binary_search( pointerSRecords , argv[3], numrecords);    //i call the binary function and assign the return to an integer value which is ResultOfThebinarySearch

	if   (ResultOfThebinarySearch == -1){                                     // if condition : to check if the LastName is in the List , if not then print this statement
		printf("No record found for student with last name %s.\n", argv[3]);
	}

	else{
		printf("The following record was found:\n");            // else condition to print the records if it's in the list
		printf("Name: %s %s \n", pointerSRecords[ResultOfThebinarySearch]->FirstNames, pointerSRecords[ResultOfThebinarySearch]->LastNames);
		printf("Student ID: %d \n", pointerSRecords[ResultOfThebinarySearch]->IDNums);
		printf("Student Grade: %d \n", pointerSRecords[ResultOfThebinarySearch]->Marks);

	}

}



