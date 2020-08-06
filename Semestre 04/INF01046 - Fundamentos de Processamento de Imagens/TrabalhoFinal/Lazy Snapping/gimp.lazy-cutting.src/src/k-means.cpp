#include <iostream>
#include <vector>

using namespace std;
/*
 * K-Means class
 * dim: dimension of the vector
 * k: number of clusters
 */
template <int dim, int k, typename T = float>
class KMeans{

private:

  /*
   * Attribute declaration
   */

  typedef typename vector<T>::iterator Iterator;

  /* vector of currentCluster, storing
   * the cluster index the data has been assigned to
   * and if it has changed since the last iteration
   */
  struct currentCluster{
    currentCluster():changed(true), index(-1){}
    bool changed;
    int index;
  };

  vector<currentCluster> changeVector;
  
  /*
   * vector of currentCluster, storing
   * the cluster index the data has been assigned to
   * and if it has changed since the last iteration
   */
  struct cluster{
    cluster():pos(dim,0),numOfMembers(0){}

    vector<T> pos;
    int numOfMembers;
  };

  /* Stores the value of each cluster */
  vector<cluster> clusters;
 

  /* 
   * Function declaration
   */


  /*
   * Use the first k data of the dataset
   * as initial centroids
   */
  void init(const vector<T>& data, vector<T>& centroids)
  {
    // Resize chage vector
    changeVector.resize(data.size()/dim,currentCluster());
    
    // take some 'random' samples of the data, for the initialization
    int dist = data.size()/(k-1);
    dist = dist/dim;
    dist = dist*dim;

    for (unsigned i = 0, t = 0; t < centroids.size(); i+=dist, t+=dim){
      for(unsigned j = 0; j < dim; j++)
	centroids[t+j] = data[i+j];
    }
}


  /*
   * Compute the new centroid from
   * the clusters.
   */
  void centroidComputation(vector<T>& centroids)
  {
    // Iterate over all centroids
    for (unsigned i = 0, t = 0; i < clusters.size(); i++, t += dim){
      int members = clusters[i].numOfMembers;
      clusters[i].numOfMembers = 0;
      
      
      // Iterate over the dimension
      for (int j = 0; j < dim; j++){
	if (members != 0)
	  centroids[t+j] = (clusters[i].pos[j])/members;
	
	// set position back to zero
	clusters[i].pos[j] = 0;
      } 
         
    }
    
  }
  

  /*
   * Compute min distance between centroid and
   * data value v1
   */
  float distanceComputation(Iterator centroid, Iterator v1)
  {
    float dist = 0;
    for (Iterator it = centroid; it < centroid+dim; it++, v1++)
      dist += (*v1 - *it)*(*v1 - *it);

    return dist;
  }


  /*
   * Grouping is based on the minimum distance
   */
  void grouping(vector<T>& data, vector<T>& result)
  {
    
    int index; // index of best fitting cluster
    float minVal;
    float val;

    // iterate over all dataSet
    for (unsigned i = 0, t = 0; i < data.size(); i += dim, t++){
      
      minVal = distanceComputation(result.begin()+0, data.begin()+i);
      index = 0;

        
      // iterate over all centroids
      // and find the acording cluster
      int idx = 1;
      for (unsigned j = dim; j < result.size(); j += dim, idx++){
	val = distanceComputation(result.begin()+j, data.begin()+i);
	if (val < minVal){
	  index = idx;
	  minVal = val;
	}
      }

      
      // add data to acording cluster
      for (unsigned j = 0; j < clusters[index].pos.size(); j++){	
	clusters[index].pos[j] += data[i+j];
      }
      clusters[index].numOfMembers++;
      
      // Update the changeVector
      changeVector[t].changed = (changeVector[t].index != index)? true: false;
      changeVector[t].index = index;
    

    }
    
  }


  bool hasChanged(const vector<currentCluster> &v)
  {
    for(unsigned i = 0; i < v.size(); i++){
      if (v[i].changed)	
	return v[i].changed;
    }
    return false;
  }

  void printVector(const vector<T>& v)
  {
    cout << "Print vector" << endl;
    for(unsigned i = 0; i < v.size(); i+=dim){
      for (int t = 0; t < dim; t++){
	cout << v[i+t] << ", ";

      }
      cout << endl;
    }
  }
public:

  // Constructor
  KMeans():clusters(k, cluster()){ }


  ~KMeans(){}
  
  void computeKMeans(vector<T>& data, vector<T>& result)
  {

    init(data, result);
    
        
    grouping(data, result);

    //printVector(result);

    centroidComputation(result);
        
    while(hasChanged(changeVector)){
      grouping(data, result);
      centroidComputation(result);      
      //printVector(result);
    } 
    
  }

    
};


// Test function
/*
int main(){  
  vector<float> testVector (8,0.f);
  vector<float> result(4,0.f);
  
  // Out put shpuld be:
  // kmeans vector:
  // Vector 0: 1.5, 1, 
  // Vector 2: 4.5, 3.5, 
  testVector[0] = 1.f; testVector[1] = 1.f;
  testVector[2] = 2.f; testVector[3] = 1.f;
  testVector[4] = 4.f; testVector[5] = 3.f;
  testVector[6] = 5.f; testVector[7] = 4.f;

  kmeans<2,2> kmean;
  
  kmean.computeKMeans(testVector, result);

  cout << endl << "kmeans vector:" << endl;
  for(unsigned i = 0; i < result.size(); i+=2){
    cout << "Vector " << i << ": ";
    for(unsigned j = 0; j < 2; j++){
      cout << result[i+j] << ", ";
    }
    cout << endl;
  }

  return 1;
}

*/
