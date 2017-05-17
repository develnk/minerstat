#ifndef ALGORITHM_INTERFACE_H
#define ALGORITHM_INTERFACE_H


class Algorithm_Interface
{
public:
  virtual ~Algorithm_Interface() {}
  virtual bool checkSettings() = 0;
  virtual void startAlgorithm() = 0;
  virtual void sendData() = 0;
};

#endif // ALGORITHM_INTERFACE_H
