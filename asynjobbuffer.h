#ifndef ASYNJOBBUFFER_H
#define ASYNJOBBUFFER_H

#include <string>
#include <map>
#include "MyMutex.h"
#include <ctime>

enum AsynJobState
{JOB_NOT_EXIST=-1, JOB_END, JOB_RUN};

/**
 * class, that describe the asynchronous job
 */
class AsynJob : private MyMutex
{
    private:
	unsigned int id;
	string name;
	AsynJobState status;
	time_t stateTimestamp;
	string result;
	bool jobCancel;		    //whether the job must be canceled immediately	
	
	public:    
	    /**
	     * constructor
	     * @param jobId
	     * @param jobName
	     */
	    AsynJob (unsigned int jobId, string jobName);
	    
	    /**
	     * get the job id
	     * @return job id
	     */
	    inline unsigned int getId ()
	    { return id;}
	    
	    /**
	     * get the job name
	     * @return job name
	     */
	    inline string getName ()
	    { return name;}
	    
	    /**
	     * get current job status
	     * @return current job status
	     */
	    AsynJobState getStatus ();
	    
	    /**
	     * get job result
	     * @return job result
	     */
	    string getResult ();
	    
	    /**
	     * set job status and result
	     * @param st job status
	     * @param res job result
	     */
	    void setStatusAndResult (AsynJobState st, string res);
	    
	    /**
	     * get true if this job is canceled or should be canceled immediately
	     * @return true-if job canceled or should be canceled immediately
	     */
	    inline bool isCanceled ()
	    {return jobCancel;}
	    
	    /**
	    * cancel this job if it not ends alreads
	    */
	    void cancel();
	    
	    /**
	    * get time stamp of current state
	    * @return time stamp of current state
	    */
	    time_t getStateTimestamp();
};

/**
 * class, that collect the asynchronous jobs
 */
class AsynJobBuffer : private MyMutex
{
    private:
	map<unsigned int, AsynJob*> asynJobList;	//mapping list of asyn. job id to AsynJob
	unsigned int jobCounter;	
	
	public:
	    AsynJobBuffer();
	    
	    /**
	    * destructor
	    * remove all internal elements
	    */
	   ~AsynJobBuffer();	   	   
	   
	   /**
	    * create id for new asyn job
	    * @return new job id
	    */
	   unsigned int getNewJobId ();
	   
	   /**
	   * stop all asyn. jobs and remove it from this buffer
	   */
	   void clearAll();
	   
	   /**
	   * add new asyn. job to this buffer
	   * @param job new job
	   */
	   void addJob(AsynJob* job);
	   
	   /**
	   * remove asyn. job with id 'id' from this buffer
	   * @param id id of job, that must be removed
	   */
	   void removeJob(unsigned int id);
	   
	   /**
	   * get job with id 'id'
	   * @param id id of job, that must be returned
	   * @return job; return null if no job found
	   */
	   AsynJob* getJob(unsigned int id);
           
           /**
           * get true if job with id 'id' is available in the buffer
           * @param id job id
           * @return true or false
           */
           bool isJobAvailable(unsigned int id);
	   
	   /**
	    * get true if job with id 'id' is canceled or does not exist
	    * @param id job id
	    * @return true-if job canceled or does not exist;
	    */
           bool isJobCanceled(unsigned int id);
	   
	   /**
	    * cancel job with id 'id'
	    * @param id job id	    
	    */
           void cancelJob(unsigned int id);
	   
	   /**
	    * get status of job with id 'jobId'
	    * @return current job status
	    */
	   AsynJobState getJobStatus (unsigned int jobId);
	   
	   /**
	    * get result of job with id 'jobId'
	    * @return job result
	    */
	   string getJobResult (unsigned int jobId);
	   
	   /**
	    * get ids and timestamp of the state of all jobs, which are of state 'state'
	    * @param state job state
	    * @return list with job ids and timestamp of this state
	    */
	   map<unsigned int, time_t>* getJobStateTimestamp (AsynJobState state);
};

#endif
