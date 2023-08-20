// for(int i=0; i<numOfTransactions; i++)
    // {
    //     int shmid = shmget(IPC_PRIVATE, sizeof(int), 0666);
    //     if(shmid == -1)
    //     {
    //         perror("shmget");
    //         return -1;
    //     }

    //     char* c_message = (char*) shmat(shmid, (void*)0, 0);
        
    //     // initialize random seed
    //     srand(time(NULL));

    //     // generating a random number as the number of lines we will get
    //     int line_num = rand() % numOfLines + 1 

    //     string message = "Bring the line ";
    //     message.append(to_string(line_num));
    //     message.append(" from the file.");

    //     strcpy(c_message, message.c_str());

    //     shmdt(c_message);

    // }