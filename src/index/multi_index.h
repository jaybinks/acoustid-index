// Copyright (C) 2021  Lukas Lalinsky
// Distributed under the MIT license, see the LICENSE file for details.

#ifndef ACOUSTID_INDEX_MULTI_INDEX_H_
#define ACOUSTID_INDEX_MULTI_INDEX_H_

#include <QMap>
#include <QPointer>
#include <QSharedPointer>
#include <QThreadPool>
#include <QString>

#include "index.h"
#include "store/directory.h"

namespace Acoustid {

class MultiIndex {
 public:
    MultiIndex();

    void addIndex(const QString &name, const QSharedPointer<Index> &index);

    void close();

    QThreadPool *threadPool() const;
    void setThreadPool(QThreadPool *pool);

    bool indexExists(const QString &name);
    QSharedPointer<Index> getIndex(const QString &name, bool create = false);
    void createIndex(const QString &name);
    void deleteIndex(const QString &name);

 private:
    QMutex m_mutex;
    QMap<QString, QSharedPointer<Index>> m_indexes;
    QPointer<QThreadPool> m_threadPool;
};

}  // namespace Acoustid

#endif  // ACOUSTID_INDEX_MULTI_INDEX_H_
