#include "../Model.hpp"
#include <memory>
class StateSaver {
public:
  StateSaver(std::shared_ptr<DataModel> givenModel) : dataModel(givenModel) {
    /*
            Establish filesystem path to new trial for each run in a new folder
       in the Evaluation folder. Set up a ROS2 folder within the new folder. Set
       up a QT user logging folder within the new folder.
    */
  }
  /* For start(), pause(), and end()
  The thread used to call this function should return back to its caller.
  In order to control StateSaver's state, threads compete for either a mutex or
  atomic data collection to control the state which for now is start, pause, and
  end.
  */
  std::shared_ptr<std::mutex> State_saver_mutex;
  void start();
  void pause();
  void end();

private:
  std::shared_ptr<DataModel> dataModel;
};