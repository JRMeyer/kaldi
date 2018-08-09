// gmmbin/pdf-to-phone.cc

// Copyright 2009-2012  Microsoft Corporation  Johns Hopkins University (Author: Daniel Povey)
//                     Johns Hopkins University  (author: Guoguo Chen)

// See ../../COPYING for clarification regarding multiple authors
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
// THIS CODE IS PROVIDED *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY IMPLIED
// WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE,
// MERCHANTABLITY OR NON-INFRINGEMENT.
// See the Apache 2 License for the specific language governing permissions and
// limitations under the License.


#include "base/kaldi-common.h"
#include "util/common-utils.h"
#include "gmm/am-diag-gmm.h"
#include "hmm/transition-model.h"
#include "gmm/mle-am-diag-gmm.h"
#include "tree/build-tree-utils.h"
#include "tree/context-dep.h"
#include "tree/clusterable-classes.h"
#include "util/text-utils.h"




namespace kaldi {

  void pdfToPhone(const std::vector<int32> &pdf_id,
                  const TransitionModel &trans_model) {
      std::vector<int32> phones;
      GetPhonesForPdfs(trans_model, pdf_id, &phones);
      std::ostringstream ss;      
      for (int32 idx = 0; idx < phones.size(); idx ++)
          ss << phones[idx] << ' ';
      std::cout << "Tree has pdf-id " << pdf_id[0] 
          << " with corresponding phone list: " << ss.str();
  }

}


  
int main(int argc, char *argv[]) {
  using namespace kaldi;
  typedef kaldi::int32 int32;
  
  const char *usage =
    "Get a list of corresponding phones for a pdf-id in a decision tree\n"
    "Usage:  pdf-to-phone <pdf-id> <tree-in> <topo-in>\n"
    "e.g.: \n"
    "  pdf-to-phone 231 tree topo\n";
  
  
  ParseOptions po(usage);
  po.Read(argc, argv);
  
  std::string
      pdf_id = po.GetArg(1),     
      tree_filename = po.GetArg(2),
      topo_filename = po.GetArg(3);
    
  ContextDependency ctx_dep; ReadKaldiObject(tree_filename, &ctx_dep);
  HmmTopology topo; ReadKaldiObject(topo_filename, &topo);
  TransitionModel trans_model(ctx_dep, topo);

  std::vector<int32> pdf(1, stoi(pdf_id));
    
  pdfToPhone(pdf, trans_model); 

}
