# gem5ex1
Introduction to gem5 
# Ερωτήματα Πρώτου Μέρους

## Ερώτημα 1
Τρέχουμε την εντολή:
  ```
  $ ./build/ARM/gem5.opt configs/example/arm/starter_se.py --cpu="minor" "tests/test-progs/hello/bin/arm/linux/hello"
  ```
  #### Τα default χαρακτηριστικά του συστήματος που έχουν περάσει ως παράμετροι στον gem5 είναι:
  
  CPU type: minorCPU όπως ορίσαμε στο command prompt
  
  CPU frequency: 1GHz
  
  Number of cores: 1
  
  Memory type: DDR3_1600_8x8
  
  Physical Memory Size: 2GB
  
  Memory Channels: 2
  
  Και οι cache που επιλέγονται και πάλι ως defaults στον minor είναι: L1 Data Cache, L1 Instruction Cache, TLB (“Walk”) Cache, L2 Cache
  
  Θα μπορούσαμε να αλλάξουμε τη συχνότητα του ρολογιού του επεξεργαστή προσθέτοντας ως όρισμα το “--cpu-freq=xGHz” στην αρχική εντολή (θέτοντας έτσι τη συχνότητα x GHz) 

## Ερώτημα 2 
Με βάση το αρχείο που προκύπτει ([HelloWorld.txt](https://github.com/nicholasterzis/gem5ex1/files/7614517/HelloWorld.txt)) παίρνουμε τις ακόλουθες τιμές:

  sim_insts: 	65482
  
  sim_seconds: 	0.000035
  
  host_inst_rate: 	42120

## Ερώτημα 3
Από τα αρχεία config.ini, config.json και HelloWorld παίρνουμε τις τιμές:

  IL1.miss_nu = 		327
  
  DL1.miss_nu = 		177
  
  L2.miss_nu =		474
  
  Total_Inst_nu = 	5027 
  
  Έτσι προκύπτει CPI = 6.316093097

## Ερώτημα 4
Οι τύποι in-order CPUs (επεξεργαστές που εκτελούν κάθε εντολή μόνο μετά το πέρας της προηγούμενης) που χρησιμοποιεί ο gem5 είναι οι ακόλουθοι:

  ### SIMPLE CPU
  Ο SimpleCPU είναι ένα συμβολικό in-order μοντέλο που χρησιμοποιείται όταν δεν απαιτείται η χρήση πιο λεπτομερών μοντέλων. Δεν διαθέτει συγκεκριμένο pipeline και γι’αυτό δεν θεωρείται αντιπροσωπευτικός ενός πραγματικού CPU. Η βασική του κλάση BaseSimpleCPU διαθέτει εντολές που γράφουν και διαβάζουν τη μνήμη και καθορίζουν τι θα συμβεί κάθε κύκλο του ρολογιού. Η κλάση χρησιμοποιείται μέσω των δύο θυγατρικών της κλάσεων AtomicSimpleCPU και TimingSimpleCPU ανάλογα με τον τρόπο με τον οποίο λειτουργεί η προσπέλαση της μνήμης. O AtomicSimpleCPU χρησιμοποιεί το λεγόμενο “atomic memory access”, κατά το οποίο τα δεδομένα από την επιστροφή κάθε request στη μνήμη που σχετίζονται με την καθυστέρηση (latency), χρησιμοποιούνται για να υπολογισθεί μια προσέγγιση του χρόνου που παίρνει η κάθε προσπέλαση της μνήμης cache. Τα αιτήματα προσπέλασης γίνονται χωρίς να έρχεται απάντηση και τελειώνουν κατευθείαν βασιζόμενα στην έννοια της ατομικότητας κατά την οποία μια εντολή εκτελείται σαν ένα σύνολο και χωρίς να σπάει σε μικρότερα τμήματα με αποτέλεσμα να ολοκληρώνεται πλήρως ή να μην εκτελείται καθόλου. Ο TimingSimpleCPU λαμβάνει υπόψη του τις καθυστερήσεις που μπορεί να προκύψουν κατά τη μετακίνηση των πακέτων και εξαιτίας της κοινής χρήσης υλικού, με το κάθε αίτημα προσπέλασης να δέχεται απάντηση από τη μνήμη ή μήνυμα μη αναγνώρισης (NACK) σε περίπτωση που το αίτημα δεν μπορεί να ολοκληρωθεί λόγω σφάλματος. Οι μέθοδοι που χρησιμοποιούνται για την διαχείριση των απαντήσεων αυτών αποτελούν κι αυτές μέρος του μοντέλου TimingSimple. 

  ### MINOR CPU 
  Ο MinorCPU είναι ένα in-order μοντέλο CPU με τέσσερα στάδια στον κύκλο εντολών του: fetch1, fetch2, decode και execute. Το fetch1 είναι το στάδιο υπεύθυνο για την προσπέλαση της TLB (Transaction Lookaside Buffer) Cache και για την ανάκληση (fetching) της εντολής από την κύρια μνήμη. Το fetch2 είναι το στάδιο που περιλαμβάνει τον μηχανισμό πρόβλεψης της επόμενης εντολής (branch prediction) και είναι το σημείο που τα δεδομένα που λαμβάνονται στο fetch1 χωρίζονται σε ξεχωριστές εντολές για να περάσουν στο στάδιο της αποκωδικοποίησης (decode). Τέλος το στάδιο της εκτέλεσης περιλαμβάνει όλες τις διαδικασίες προσπέλασης μνήμης και εκτέλεσης εντολών (issue, commit, execute) καθώς και αυτό της επανεγγραφής στη μνήμη (writeback). Αξίζει να σημειωθεί πως ο MinorCPU μπορεί να χρησιμοποιηθεί και για multithreading. Δύο ακόμη γνωστά μοντέλα που βασίζονται στον MinorCPU είναι τα HPI και ex5_LITTLE.

### 4a
To αρχείο main.c (εδώ το χρησιμοποιούμε μετά την μετατροπή του σε main_arm) είναι ένα πρόγραμμα σε C που υπολογίζει και εκτυπώνει τους n πρώτους αριθμούς της ακολουθίας  fibonacci. Εδώ το χρησιμοποιούμε για n=10 (η παράμετρος αρχικοποιείται εντός του προγράμματος). 
#include <stdio.h>

```
int
main ()
{
  int n = 10;
  int fib = 1;
  int prev = 1;
  int temp = 0;
  for (int i = 0; i < n; i++)
    {
      if (i == 0 || i == 1)
	{
	  printf ("1 ");
	}
      else
	{
	  temp = fib;
	  fib += prev;
	  prev = temp;
	  printf ("%d ", fib);
	}
    }

  return 0;
}
```
Τρέχουμε την παρακάτω εντολή, θέτοντας τη συχνότητα στο 1GHz, τον τύπο επεξεργαστή σε MinorCPU και τον τύπο μνήμης σε DDR3_1600_8x8:
  ```
  $ ./build/ARM/gem5.opt configs/example/se.py --cpu-type=MinorCPU --cpu-clock=1GHz --mem-type=”DDR3_1600_8x8” --caches --l2cache --cmd=tests/main_arm
  ```
  
  #### Και για επεξεργαστή τύπου TimingSimpleCPU:
  ```
  $ ./build/ARM/gem5.opt configs/example/se.py --cpu-type= TimingSimpleCPU --cpu-clock=1GHz --mem-type=”DDR3_1600_8x8” --caches --l2cache --cmd=tests/main_arm
  ```
  
Οι χρόνοι που προκύπτουν από τα αρχεία [Minor.txt](https://github.com/nicholasterzis/gem5ex1/files/7614525/Minor.txt) και [TS.txt](https://github.com/nicholasterzis/gem5ex1/files/7614526/TS.txt):
  
  MinorCPU: 0.000067s
  
  TimingSimpleCPU: 0.000084s
  
  

### 4b
#### Αντίστοιχα για συχνότητα ρολογιού 2.2GHz και 0.5GHz:
  ```
  $ ./build/ARM/gem5.opt configs/example/se.py --cpu-type=MinorCPU --cpu-clock=2.2GHz --mem-type=”DDR3_1600_8x8” --caches --l2cache --cmd=tests/main_arm
  ```
  
  ```
  $ ./build/ARM/gem5.opt configs/example/se.py --cpu-type=TimingSimpleCPU --cpu-clock=2.2GHz --mem-type=”DDR3_1600_8x8” --caches --l2cache --cmd=tests/main_arm
  ```
  
  Οι χρόνοι που προκύπτουν από τα αρχεία [Minor2.2.txt](https://github.com/nicholasterzis/gem5ex1/files/7614527/Minor2.2.txt) και [TS2.2.txt](https://github.com/nicholasterzis/gem5ex1/files/7614528/TS2.2.txt):
  
  MinorCPU: 0.000045s
  
  TimingSimpleCPU: 0.000052s
  
  ```
  $ ./build/ARM/gem5.opt configs/example/se.py --cpu-type=MinorCPU --cpu-clock=0.5GHz --mem-type=”DDR3_1600_8x8” --caches --l2cache --cmd=tests/main_arm
  ```
  
  ```
  $ ./build/ARM/gem5.opt configs/example/se.py --cpu-type= TimingSimpleCPU --cpu-clock=0.5GHz --mem-type=”DDR3_1600_8x8” --caches --l2cache --cmd=tests/main_arm
  ```
  
 Οι χρόνοι που προκύπτουν από τα αρχεία [Minor0.5.txt](https://github.com/nicholasterzis/gem5ex1/files/7614531/Minor0.5.txt) και [TS0.5.txt](https://github.com/nicholasterzis/gem5ex1/files/7614530/TS0.5.txt):
  
  MinorCPU: 0.000108s
  
  TimingSimpleCPU: 0.000144s
  

  #### Αλλάζοντας τη μνήμη σε LPDDR3_1600_1x32 και SimpleMemory αντίστοιχα:
  ```
  $ ./build/ARM/gem5.opt configs/example/se.py --cpu-type=MinorCPU --cpu-clock=1GHz --mem-type=”LPDDR3_1600_1x32” --caches --l2cache --cmd=tests/main_arm
  ```
  
  ```
  $ ./build/ARM/gem5.opt configs/example/se.py --cpu-type= TimingSimpleCPU --cpu-clock=1GHz --mem-type=”LPDDR3_1600_1x32” --caches --l2cache --cmd=tests/main_arm
  ```
  
 Οι χρόνοι που προκύπτουν από τα αρχεία [MinorLPDDR3.txt](https://github.com/nicholasterzis/gem5ex1/files/7614532/MinorLPDDR3.txt) και [TSLPDDR3.txt](https://github.com/nicholasterzis/gem5ex1/files/7614533/TSLPDDR3.txt):
  
  MinorCPU: 0.000072s
  
  TimingSimpleCPU: 0.000088s
  
  ```
  $ ./build/ARM/gem5.opt configs/example/se.py --cpu-type=MinorCPU --cpu-clock=1GHz --mem-type=”SimpleMemory” --caches --l2cache --cmd=tests/main_arm
  ```
  
  ```  
  $ ./build/ARM/gem5.opt configs/example/se.py --cpu-type= TimingSimpleCPU --cpu-clock=1GHz --mem-type=”SimpleMemory” --caches --l2cache --cmd=tests/main_arm 
  ```
  Οι χρόνοι που προκύπτουν από τα αρχεία [MinorSM.txt](https://github.com/nicholasterzis/gem5ex1/files/7614538/MinorSM.txt)
 και [TSSM.txt](https://github.com/nicholasterzis/gem5ex1/files/7614536/TSSM.txt):
  
  MinorCPU: 0.000059s
  
  TimingSimpleCPU: 0.000076s
  

  Ποσοστιαία, παρατηρούμε πως ο MinorCPU είναι πιο ευαίσθητος στη μεταβολή της συχνότητας του ρολογιού και λιγότερο στη μεταβολή του τύπου μνήμης σε σχέση με τον TimingSimpleCPU. Η ευαισθησία του TimingSimpleCPU στην μεταβολή της μνήμης μπορεί να εξηγηθεί από τον τρόπο λειτουργίας του καθώς σε μια πιο γρήγορη μνήμη η διαχείριση των αιτημάτων προσπέλασης και των αντίστοιχων απαντήσεων που δέχεται αυτό το μοντέλο επεξεργαστή, μπορεί να γίνει πιο γρήγορα. Λόγω της έλλειψης pipeline η πλειοψηφία του χρόνου που καθυστερεί το συγκεκριμένο μοντέλο οφείλεται στην επικοινωνία αυτή με τις μνήμες, οπότε η επιλογή μίας ταχύτερης μνήμης έχει μεγαλύτερη επίδραση στην ολική του επίδοση, ενώ αυτή δεν εξαρτάται τόσο από την ταχύτητα του ρολογιού. Επίσης πειραματικά προκύπτει πως ο MinorCPU έχει καλύτερες επιδόσεις από τον TimingSimpleCPU κάτι που αντιβαίνει στην γνωστή βιβλιογραφία σύμφωνα με την οποία το μοντέλο simple, όντας πιο απλό στον σχεδιασμό του και αφαιρώντας τα τμήματα εκείνα του Minor μοντέλου που το κάνουν πιο σωστό στην προσέγγιση ενός κανονικού cpu (πχ pipeline), είναι πιο γρήγορο.

## Βιβλιογραφία:

  https://www.gem5.org/documentation/general_docs/cpu_models/SimpleCPU
  
  https://en.wikipedia.org/wiki/Atomicity_(database_systems)
  
  https://www.gem5.org/documentation/general_docs/memory_system/index.html#access-types
  
  http://architecture.di.uoa.gr/5plus4.2.html 
  
  https://www.gem5.org/documentation/general_docs/cpu_models/minor_cpu
  
  https://nitish2112.github.io/post/gem5-minor-cpu/
  
  https://cirosantilli.com/linux-kernel-module-cheat/#gem5-cpu-types
