#ifndef __CLUSTERING_ADMINSTRATION_HTTP_SERVER_HPP__
#define __CLUSTERING_ADMINSTRATION_HTTP_SERVER_HPP__

#include "clustering/administration/issues/global.hpp"
#include "clustering/administration/metadata.hpp"
#include "http/http.hpp"
#include "mock/dummy_protocol.hpp"
#include "mock/dummy_protocol_json_adapter.hpp"
#include "rpc/semilattice/view.hpp"

class blueprint_http_server_t : public http_server_t {
    typedef semilattice_readwrite_view_t<cluster_semilattice_metadata_t> internal_view_t;
    typedef directory_rwview_t<cluster_directory_metadata_t> directory_view_t;

public:
    blueprint_http_server_t(boost::shared_ptr<internal_view_t> _semilattice_metadata, 
                            clone_ptr_t<directory_view_t> _directory_metadata,
                            boost::uuids::uuid _us,
                            global_issue_tracker_t *_issue_tracker,
                            int port)
        : http_server_t(port), semilattice_metadata(_semilattice_metadata), 
          directory_metadata(_directory_metadata), us(_us),
          issue_tracker(_issue_tracker)
    { }

    blueprint_http_server_t(boost::shared_ptr<internal_view_t> _semilattice_metadata, 
                            clone_ptr_t<directory_view_t> _directory_metadata,
                            boost::uuids::uuid _us,
                            global_issue_tracker_t *_issue_tracker)
        : http_server_t(), semilattice_metadata(_semilattice_metadata), 
          directory_metadata(_directory_metadata), us(_us),
          issue_tracker(_issue_tracker)
    { }

private:
    http_res_t handle(const http_req_t &);

    boost::shared_ptr<internal_view_t> semilattice_metadata;
    clone_ptr_t<directory_view_t> directory_metadata;

    boost::uuids::uuid us;

    global_issue_tracker_t *issue_tracker;
};

#endif
