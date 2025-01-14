Οδηγίες εκτέλεσης: Κάνετε make στο κεντρικό directory και έπειτα cd modules ώστε να τρέξετε τα εκτελέσιμα. Για Game_of_Life και exercise2 τα εκτελείτε ως εξής :mpiexec -n <processes> Game_of_Life <size_of_matrix> <births(1000)>
                                mpiexec -n <processes> exercise2 <size_of_matrix>


Για να δημιουργήσετε processes σε διαφορετικούς κόμβους από το machines αρχείο μπορείτε να το τρέξετε ως εξής:  
mpiexec -machinefile machines -n <processes> Game_of_Life <size_of_matrix> <births(1000)>

Για το σειριακό πρόγραμμα Serial_exercise2.c Απλά το εκτελείτε ./Serial_exercise <size_of_matrix>
