    #include <stdlib.h>
    #include <stdio.h>
    #include <math.h>

    /*
        Marmara University Computer Engineering Department CSE2225 Data Structures Class Project #2

            -Constructing a BST with 3log(4n) depth levels and best possible access time-

        Name Surname : Mustafa Tunahan BAŞ
        No : 150119055
    */

    int Maxd(int a,int b)
    {
        return a>=b ? a : b;
    }

    int Mind(int a,int b)
    {
        return a>=b ? b:a; 
    }

    float Maxf(float a,float b)
    {
        return a>=b ? a: b;
    }

    float Minf(float a,float b)
    {
        return a>=b ? b:a;
    }

    float Abs(float num)
    {
        return num<0 ? -num : num;
    }

    /*
      You can change the data type the other functions and consts related to the data type to use them with your own logic and 
      it will work just fine except for the functions where type specific logic is implemented(you should change them too obviously)
    */
    struct DataType
    {   
        int numberData;
    } typedef Data;

    int Compare(Data a,Data b)
    {
        //You should implement your own logic here for different data types than numbers
        return a.numberData>b.numberData ? 1 : 0;
    }

    int Equals(Data a,Data b)
    {
        //You should implement your own logic here for different data types than numbers
        return a.numberData==b.numberData;
    }

    const Data defaultData = {0};
    const Data minData = {INT_MIN};
    const Data maxData = {INT_MAX};
    
    Data GetDefaultData()
    {
        //Change here if your default data can't be created in one line
        return defaultData;
    }

    Data GetMinData()
    {
        return minData;
    }

    Data GetMaxData()
    {
        return maxData;
    }

    //A data structure to hold a Data array and its length
    struct DataArrayHolder
    {
        Data* array;
        int length;
    } typedef DataArrayHolder;

    struct BSTNode
    {
        Data data;
        struct BSTNode* parent;
        struct BSTNode* left;
        struct BSTNode* right;
    } typedef Bst;

    Bst* CreateNode(Bst* parent,Data data)
    {
        Bst* bst = (Bst*)malloc(sizeof(Bst));
        bst->parent=parent;
        bst->left=NULL;
        bst->right=NULL;
        bst->data=data;
        return bst;
    }

    Bst* InsertNode(Bst** bst,Bst* parent,Data data)
    {
        if(*bst==NULL)
        {
            *bst = CreateNode(parent,data);
            return *bst;
        }
        else if(Compare((*bst)->data,data))
            return InsertNode(&((*bst)->left),*bst,data);
        else 
            return InsertNode(&((*bst)->right),*bst,data);
    }

    Bst* FindMin(Bst* bst)
    {
        while (bst->left!=NULL)
            bst=bst->left;
        
        return bst;
    }

    Bst* FindMax(Bst* bst)
    {
        while (bst->right!=NULL)
            bst=bst->right;
        
        return bst;
    }

    int GetHeight(Bst* bst)
    {
        if(bst==NULL) return 0;
        return Maxd(GetHeight(bst->left),GetHeight(bst->right))+1;
    }

    int IsLeaf(Bst* bst)
    {
        if(bst->left==NULL && bst->right==NULL) return 1;
        return 0;
    }

    Bst* Find(Bst* bst,Data data)
    {
        if(bst==NULL)
            return NULL;
        else if(Equals(bst->data,data))
            return bst;
        else if(Compare(bst->data,data))
            Find(bst->left,data);
        else
            Find(bst->right,data);
    }

    void GetOrderAndDepth(Bst* bst,int*depth,int* order)
    {
        int depthlevel=0,index=0;

        do
        {
            index += (Compare(bst->data,(bst->parent==NULL ? GetMaxData() : bst->parent->data)) * (int)pow(2,depthlevel++));
        } while ((bst=bst->parent)!=NULL);

        *depth=depthlevel-1;
        *order=index+1;
    }

    //Pass 1 as current always
    int GetNodeCountAtDepth(Bst* root,int depth,int current)
    {
        if(root==NULL) return 0;
        else if(depth==(current++)) return 1;
        else return GetNodeCountAtDepth(root->left,depth,current) + GetNodeCountAtDepth(root->right,depth,current);
    }

    //Gets the text from input.txt
    char* ReadFile()
    {
        int size=1;
        char *nums = (char*)malloc(size*sizeof(char));
        int ch;
        FILE* file = fopen("input.txt","r");
        size_t len = 0;
        
        while((ch=fgetc(file))!=EOF && ch != '\n')
        {
            nums[len++]=ch;
            if(len==size)
                nums = realloc(nums, sizeof(char)*(size+=4));
        }

        fclose(file);

        nums[len]='\0';
        nums = realloc(nums,sizeof(char)*len);

        return nums;
    }

    int* GetNumberIndexes(char* nums,int* numberCount)
    {
        int size=1;
        int* indexes = (int*)malloc(sizeof(int)*size);
        int nmbCount=0;
        int index=0;
        int numIndex=0;
        int isNum=0;
        int num;
        const int space = 32 - '0';
        const int minus = '-' - '0';

        while (*nums!='\0')
        {
        	if(index==536870911)
            {
            	printf("It's mathematically impossible to insert more than 536870911 numbers in a BST with 3log(4n) depth levels only!");
            	exit(0);
			}
        	
            num = *nums - '0';

            if(num==space)
            {
                if(isNum)
                {
                    *(indexes + nmbCount++) = numIndex;

                    if(nmbCount==size)
                        indexes = realloc(indexes, sizeof(int)*(size+=4));
                }
            
                *nums = '\0';
                isNum=0;
            }
            else if(num == minus)
            {
                printf("Negative keys are not allowed!");
                exit(0);
            }
            else if(num>=0 && num<=9)
            {
                if(!isNum)
                    numIndex=index;

                isNum=1;
            }
            else
            {
                printf("Invalid input format!");
                exit(0);
            }

            index++;
            nums++;
        }

        if(isNum)
            *(indexes + nmbCount++) = numIndex;

        *numberCount=nmbCount;
        return indexes;
    }

    //For debugging purposes
    void printd(int decimal)
    {
        printf("%d",decimal);
    }

    void WriteLine(char* string)
    {
        printf("%s\n",string);
    }

    //For debugging purposes
    void PrintArray(Data* arr,int length)
    {
        for (size_t i = 0; i < length; i++)
        {
            printd(arr[i].numberData);
            printf("\n");
        }
    }

    DataArrayHolder* GetNumbers()
    {
        int numberCount=0;

        //Get the text from input.txt
        char* numsText = ReadFile();

        //Gets the start indexes of numbers from the text
        int* indexes = GetNumberIndexes(numsText,&numberCount);

        Data* numbers = (Data*)malloc(sizeof(Data)*numberCount);

        if(numberCount<16)
        {
            //Node count can't be 0 since log(0) is undefined
            printf("Less than 16 nodes are not allowed!");
            exit(0);
        }

        //Converts the numbers one by one and puts them into the numbers array
        for (int i = 0; i < numberCount; i++)
        {
            int num = (int)atoi(numsText+indexes[i]);
            if(num==0)
            {
                printf("0(Zero) as a key is not allowed!");
                exit(0);
            }

            for (size_t j = 0; j < i; j++)
            {
                if(num==numbers[j].numberData)
                {
                    printf("Duplicate keys are not allowed!\nDuplicate : %d",num);
                    exit(0);
                }
            }

            numbers[i].numberData = num;
        }

        DataArrayHolder *arr = (DataArrayHolder*)malloc(sizeof(DataArrayHolder));
        arr->array=numbers;
        arr->length=numberCount;
        return arr;
    } 

    void Swap(Data* a,Data* b)
    {
        Data temp = *a;
        *a = *b;
        *b = temp;
    }

    /*
      Since performance does not matter that much and input size will not be given too big,
      a simple bubblesort is actually enough for the problem.
    */
    void BubbleSort(Data* arr, int length)
    {
        int whole,unsorted;
        for (whole = 0; whole < length-1; whole++)     
        {
            for (unsorted = 0; unsorted < length-whole-1; unsorted++)
            {
                if (Compare(arr[unsorted],arr[unsorted+1]))
                    Swap(arr + unsorted,arr + unsorted+1);
            }
        }
    }

    void ReverseArray(Data* arr,int length)
    {
        for (size_t i = 0; i < length/2; i++)
            Swap(arr+i,arr+length-i-1);
    }

    void GetArrays(DataArrayHolder* numbers,DataArrayHolder** arrBest,DataArrayHolder** arrSmallest,DataArrayHolder** arrRemaining)
    {
        /*
          Sorting the numbers array with any sorting algorithm 
          (I went for the bubblesort because performance will not matter that much since input size won't be large
          and it's also easy to implement)
        */
        BubbleSort(numbers->array,numbers->length);
        
        /*
          This ensures that the second deepest level in the best tree with 'numberCount' nodes
          will be filled entirely so that we can manipulate the last layer(depth level)
        */
        int lastFullDepthLevel = (int)log2f(numbers->length);

        //This is the number of nodes contained within these entirely filled depth levels
        int fullLevelsNodeCount = (int)pow(2,lastFullDepthLevel)-1;

        //This is the number of the remaining nodes that will be distributed to the 3*log(4n) depth levels
        int excessNodeCount=numbers->length-fullLevelsNodeCount;

        //This is the count of expected depth levels the nodes will be distributed over
        int expectedDepthLevel = (int)roundf(3*log10(4*numbers->length));

        if(expectedDepthLevel-lastFullDepthLevel>excessNodeCount)
        {
            lastFullDepthLevel--;
            fullLevelsNodeCount = (int)pow(2,lastFullDepthLevel)-1;
            excessNodeCount=numbers->length-fullLevelsNodeCount;
            /*
              These are for some exceptions (with 4 and 8 nodes [I don't know if there's more than these ones])
              that the number of free nodes which we can play with is less than the number of depth levels we should add to 
              achieve 3log(4n) depth levels.   
            */
        }


        if(lastFullDepthLevel<=0)
        {
            printf("A binary search tree with %d nodes can never have 3Log(4n) total depth levels!!",lastFullDepthLevel+2);
            exit(0);

            /*
              Trees that have 1 and 2 nodes can't mathematically have 3log(4n) depth levels,so this was the last step of
              eliminating excceptions.
            */

            /*
              After I finished writing the code have I learned that the program shouldn't accept less than 16 nodes
              and according to my math,only the trees with less than 3 node count (0,1 and 2) are invalid
              and that was my prior input validation code so I didn't want to delete it so here it is 
              (also the if block above this one will never be executed because it checks for 4 and 8)
            */
        }

        //The number of depth levels to add to achieve 3log(4n)
        int smallestCount = expectedDepthLevel-lastFullDepthLevel;

        Data* smallest = (Data*)malloc(sizeof(Data)*smallestCount);

        for (size_t i = 0; i < smallestCount; i++)
            smallest[i] = numbers->array[i];

        numbers->array+=smallestCount;
        numbers->length-=smallestCount;

        int remainingCount = excessNodeCount-smallestCount;
        Data* remaining = (Data*)malloc(sizeof(Data)*remainingCount);
        Data* best = (Data*)malloc(sizeof(Data)*fullLevelsNodeCount);

        int othersIndex=0,bestIndex=0;

        for (size_t i = 0; i < numbers->length; i++)
        {
            if(i&1 && remainingCount>othersIndex)
                remaining[othersIndex++] = numbers->array[i];
            else
                best[bestIndex++] = numbers->array[i];
        }

        *arrBest = (DataArrayHolder*)malloc(sizeof(DataArrayHolder));
        *arrRemaining = (DataArrayHolder*)malloc(sizeof(DataArrayHolder));
        *arrSmallest = (DataArrayHolder*)malloc(sizeof(DataArrayHolder));

        (*arrBest)->array=best;
        (*arrBest)->length=fullLevelsNodeCount;
        (*arrSmallest)->array=smallest;
        (*arrSmallest)->length=smallestCount;
        (*arrRemaining)->array=remaining;
        (*arrRemaining)->length=remainingCount;

        free(numbers);
    }

    void SplitAndInsertMedians(Bst** root,DataArrayHolder* arr)
    {
        if(arr->length<1) return;

        DataArrayHolder* leftArray = (DataArrayHolder*)malloc(sizeof(DataArrayHolder));
        DataArrayHolder* rightArray = (DataArrayHolder*)malloc(sizeof(DataArrayHolder));

        leftArray->length=arr->length/2;
        rightArray->length=leftArray->length;
        leftArray->array=arr->array;
        rightArray->array = arr->array+rightArray->length+1;

        Bst* temp = InsertNode(root,NULL,arr->array[rightArray->length]);
        
        SplitAndInsertMedians(root,leftArray);
        SplitAndInsertMedians(root,rightArray);
        free(rightArray);
        free(leftArray);
    }

    Bst* Construct3Log4nBST(DataArrayHolder* arrBest,DataArrayHolder* arrSmallest,DataArrayHolder* arrRemaining)
    {
        Bst* root=NULL;

        /*
          Inserting the fully filled depth levels(best access tree) with a uniform distrubition
          so that we can add smallest nodes and the remaining nodes to where we want them to be without
          having any problems
        */
        SplitAndInsertMedians(&root,arrBest);
        
        //Sorted array is reversed so that the deepest level will be a straight line from the root [a Linkedlist]
        ReverseArray(arrSmallest->array,arrSmallest->length);

        //Inserting the deepest nodes (smallest nodes) that will ensure 3log(4n) depth levels 
        for (size_t i = 0; i < arrSmallest->length; i++)
            InsertNode(&root,NULL,arrSmallest->array[i]);
        
        /*
          Inserting the remaining nodes of the tree in a way that will keep the best access time without breaking the
          3log(4n) depth level topology
        */
        for (size_t i = 0; i < arrRemaining->length; i++)
            InsertNode(&root,NULL,arrRemaining->array[i]);        
        
        //Freing the memory that is no more required 
        free(arrBest);
        free(arrRemaining);
        free(arrSmallest);
        
        return root;
    }

    void PrintDepthDetails(Bst* root)
    {
        int height = GetHeight(root);

        printf("Depth level of BST is %d\n\n",height);

        int nodeCount=0;
        
        for (size_t i = 0; i < height; i++)
            printf("Depth level %d -> %d\n\n",i,GetNodeCountAtDepth(root,i+1,1));
    }

    void ExecuteQueryLoop(Bst* root)
    {
        int userInput=0;
        int depth,order;
        Data data;
        Bst* nodeFound;
        while (1)
        {
            printf("Key value to be searched (Enter 0 to exit) : ");
            scanf("%d",&userInput);
            printf("\n");

            if(userInput<0)
                WriteLine("Invalid Input! Please enter a positive integer\n");
            else if(userInput)
            {
                data.numberData=userInput;
                nodeFound = Find(root,data);
                if(nodeFound==NULL)
                    printf("%d is not found in BST\n\n",userInput);
                else
                {
                    GetOrderAndDepth(nodeFound,&depth,&order);
                    printf("At Depth level %d, %d%s element\n\n",depth,order,order==1 ? "st" : order==2 ? "nd" : order==3 ? "rd" : "th");
                }
            }
            else
            {
                WriteLine("Exit");
                exit(1);        
            }
        }
    }    

    int main()
    {
        printf("\n");

        //Gets the numbers
        DataArrayHolder* numbers = GetNumbers();

        DataArrayHolder *arrBest,*arrRemaining,*arrSmallest;

        //Sorts the numbers and follows an algorithm to fill with them the three arrays created above to laters be inserted to the BST
        GetArrays(numbers,&arrBest,&arrSmallest,&arrRemaining);

        //Constructs the BST with the arrays
        Bst* root  = Construct3Log4nBST(arrBest,arrSmallest,arrRemaining);

        //Prints the height of the BST and node count at each depth level
        PrintDepthDetails(root);

        //Loops till user enters 0 and answers the queries
        ExecuteQueryLoop(root);
    }

    /*
        Marmara University Computer Engineering Department CSE2225 Data Structures Class Project #2
        
            -Constructing a BST with 3log(4n) depth levels and best possible access time-

        Name Surname : Mustafa Tunahan BAŞ
        School No : 150119055
    */