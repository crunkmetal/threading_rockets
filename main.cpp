
// preprocessor directives
#include <iostream>
#include <thread>
#include "About.h"
// atomic: for types that encapsulate a value whose access is guaranteed to not cause data races and can be used to synchronize memory accesses among different threads.
#include <atomic>		
#include <chrono>		// for time
#include <future>		// for promise/syncing access to different threads 
#include <mutex>		// for mutual exclusion


using namespace std;	// using standard template library namespace


// global variables
int numRockets = 10;
int dura = 0;
atomic<bool> hasBeenLaunched = false;	// atomic value used to guarantee a proper value while threading
char launchChoice;
mutex m;

// function prototypes
void launchRocket();
void pausenow(int);
void launchFunction(future<void>);


int main()
{
	About intro;						// instantiating an object of About class
	intro.appInfo();					// invoke function from About class
	cout << "\n\n  Launch sequence has been initiated...\n\n";
	cout << "  Rocket Cluster 17 engaged remotely from Main Base.\n";
	cout << "  Rockets in Cluster 17 ready for launch...\n\n";
	cout << "  Press <ENTER> to launch.";
	system("pause > nul");				// WinOS specific command to pause program w/out a message (msg is printed in line above)
	system("CLS");						// WinOS specific command to clear the console

	promise<void> exitSignal;			// Create a promise object -> an object that can store a value of type T to be retrieved 
										// by a future object (possibly in another thread), offering a synchronization point

	future<void> futureObj = exitSignal.get_future();	//Fetch future object associated with promise

	thread th(&launchFunction, move(futureObj));		// Starting Thread & move the future object in lambda function by reference
	thread::id th_ID = th.get_id();						// get the thread id

	this_thread::sleep_for(chrono::seconds(4));			// give the first rocket a chance to launch (based on timing of other combined functionality)

	cout << "  Abort sequence initiated...\n";
	exitSignal.set_value();				// Set the value in promise -> set_value stores the value into the shared state and makes the state ready
	pausenow(1);						// pause program for one second

	if (th.joinable())					// if this thread is ready to rejoin main thread...
	{
		th.join();						// join this thread back to main
		cout << "  Launch control has been transferred to Space Cadet at the Launchpad...\n";
		cout << "  Thread ID " << th_ID << " is terminated.\n\n";
	}
	else
	{
		cout << "  Thread ID " << th_ID << " termination processing...";
		pausenow(2);					// pause for two seconds
	}

	
	cout << "  Press <ENTER> to acknowledge Launch Control transfer...";
	system("pause > nul");
	system("CLS");

	cout << "\n  Static over the intercom breaks the nervous silence\n";
	cout << "  in the Launchpad Control Room, where our Space Cadet\n";
	cout << "  eagerly awaits his chance to shine.\n\n";
	pausenow(3);
	cout << "  'Space Cadet!' barks the Captain, breaking the anticipatory static.\n";
	pausenow(2);
	cout << "  'Ready Captain!' Opie replies instantly.\n";
	pausenow(2);
	cout << "  'Fire the remaining rockets at will!'\n";
	pausenow(2);
	cout << "  'Roger that Captain!'\n\n";
	cout << "  The Space Cadet, light-headed from the yelling and simply\n";
	cout << "  overwhelmed with his new responsibilities, loses consciousness.\n";
	cout << "  On his way down to the hard polished linoleum floor, Opie hits\n";
	cout << "  his head on the big bright red launch button...\n\n\n";
	pausenow(3);
	cout << "  Press <ENTER> to simulate Opie's head hitting the 'Launch' button...\n\n";
	system("pause > nul");
	system("CLS");

	cout << "\n  In contrasting bold letters across the Launchpad monitor, \n";
	cout << "  a message appears...\n\n";
	launchRocket();						// invoke function as usual (not in a thread)

	cout << "  Press <ENTER> to continue...\n\n";
	system("pause > nul");
	system("CLS");

	cout << "  'Cadet!' yells the Captain.\n";
	pausenow(1);
	cout << "  'Cadet! Flip the switch!'\n";
	cout << "  Unaware of Space Cadet Opie's current condition and furious\n";
	cout << "  with Opie's incompetence, the Captain flips the 'Abort' switch\n";
	cout << "  and fires the remaining rockets.\n\n";
	hasBeenLaunched = false;			// switch re-flipped to allow rockets to fire
	pausenow(5);						// pause for five seconds
	// fire remaining rockets
	do
	{
		launchRocket();
	} while (numRockets > 0);

	cout << "\n\n  Mission Complete.\n\n";
	system("pause");

	return 0;
}	// end of main function

// function with a future object as an argument, is callable (th), launch, then wait three seconds
void launchFunction(future<void> futureObj)
{
	while (futureObj.wait_for(chrono::milliseconds(1)) == future_status::timeout)
	{
		launchRocket();
		this_thread::sleep_for(chrono::milliseconds(3000));  // thread sleep for three seconds
	}
	pausenow(1);
	hasBeenLaunched = true;									// abort switch is now engaged (after launching first rocket)
	cout << "  Abort Sequence successful!\n\n";
}

// function to launch a rocket
void launchRocket()
{
	if (hasBeenLaunched == false)		// if abort switch has NOT been flipped yet...
	{
		lock_guard<mutex> guard(m);		// create and implement an instance of lock_guard for mutual exclusion benefits
		cout << "\n  *****************************\n";
		cout << "     Rocket launched!\n";
		cout << "  *****************************\n\n";
		numRockets--;					// decrement rocket count by one, each time a rocket is fired
		
		if (numRockets == 0)			// if out of rockets...
		{
			cout << "\n  ******************************************\n";
			cout << "    Cluster 17 depleted.  Reload Cluster 17.\n";
			cout << "  ******************************************\n\n";
		}
		else							// if there are rockets left, display rocket count to console
		{
			cout << "  " << numRockets << " rockets left in Cluster 17. Ready for launch...\n\n";
		}
		// m.unlock();	<- This is unnecessary, as I am using lock_guard on line 171.  .unlock() functionality auto produced with lock_guard, at end of scope
		pausenow(1);
	}
	else								// if abort switch HAS been flipped...
	{
		cout << "\n  ******************************************\n";
		cout << "    Disengage Abort switch to launch rockets.\n";
		cout << "  ******************************************\n\n";
	}
}

// function to pause program for 'x' number of seconds
void pausenow(int dura)
{
	chrono::seconds duration(dura);
	this_thread::sleep_for(chrono::seconds(duration));
}
