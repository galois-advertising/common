{$
#include <iostream>
#include <vector>
#include "databus_event.pb.h"
$}

handlername = freyja_env;
namespace=galois::freyja;

create dataview idea_view on gbus::idea_event {
    idea_id : uint64_t;
    unit_id : uint64_t;
    plan_id : uint32_t;
    user_id : uint32_t;
    xdv_ids : array uint64_t[1024u];
    title: array char[1024u];
    description : array char[1024u];
};

create datatable idea_table {
    property {
        type = HashTable;
    };
    idea_id : uint64_t;
    unit_id : uint64_t;
    plan_id : uint32_t;
    user_id  : uint32_t;
    xdv_ids : array uint64_t[1024u];
    title: array char[1024u];
    description : array char[1024u];
    (user_id, plan_id, unit_id, idea_id) : uint64key, primary_key;
};

create dataupdator idea_view -> idea_table {
    property {
        udf = idea_view_to_idea_table;
    };
};

create indextable idea_index on idea_table::user_id {};

create indexupdator idea_table -> idea_index {};
