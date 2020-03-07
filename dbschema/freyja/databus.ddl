{$
#include <iostream>
#include <vector>
#include "databus_event.pb.h"
$}

handlername = freyja_env;
namespace=galois::freyja;

create datasource gbus {
    property {
        type = databus;
        protourl = ssh://git@github.com/galois-advertising/common/master/dbschema/freyja/databus_event.proto;
    };
};