#include "Serv.h"
#include <transport/TSocket.h>
#include <transport/TBufferTransports.h>
#include <protocol/TBinaryProtocol.h>

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

using boost::shared_ptr;

int main(int argc, char **argv)
{
    boost::shared_ptr<TSocket> socket(new TSocket("localhost", 9090));
    boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));

    transport->open();

    //调用server服务
    Student s;
    s.sno = 123;
    s.sname = "hao973";
    s.ssex = 1;
    s.sage = 30;

    ServClient client(protocol);
    printf("sno=%d sname=%s ssex=%d sage=%d\n", s.sno, s.sname.c_str(), s.ssex, s.sage);
    //put
    client.put(s);
    //icall scall
    std::string strname = "";
    client.scall(strname, s);
    printf("icall=%d, scall=%s\n", client.icall(s), strname.c_str());
    //stcall
    Student stu;
    client.stcall(stu, s);
    printf("student sno=%d sname=%s ssex=%d sage=%d\n", stu.sno, stu.sname.c_str(), stu.ssex, stu.sage);

    transport->close();

    return 0;
}
