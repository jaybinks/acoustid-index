// Copyright (C) 2011  Lukas Lalinsky
// Distributed under the MIT license, see the LICENSE file for details.

#ifndef ACOUSTID_INDEX_READER_H_
#define ACOUSTID_INDEX_READER_H_

#include "common.h"
#include "segment_index.h"
#include "index.h"
#include "index_info.h"

namespace Acoustid {

class SegmentIndex;
class SegmentDataReader;
class Collector;

class IndexReader
{
public:
	IndexReader(DirectorySharedPtr dir, const IndexInfo& info);
	IndexReader(IndexSharedPtr index);
	virtual ~IndexReader();

	const IndexInfo& info() const { return m_info; }

	IndexSharedPtr index()
	{
		return m_index;
	}

	void search(const uint32_t *fingerprint, size_t length, Collector *collector, int64_t timeoutInMSecs = 0);
    std::vector<SearchResult> search(const uint32_t *fingerprint, size_t length, int64_t timeoutInMSecs = 0);

	SegmentDataReader* segmentDataReader(const SegmentInfo& segment);

protected:
	DirectorySharedPtr m_dir;
	IndexInfo m_info;
	IndexSharedPtr m_index;
};

}

#endif
