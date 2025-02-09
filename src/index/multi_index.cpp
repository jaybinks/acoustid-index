// Copyright (C) 2021  Lukas Lalinsky
// Distributed under the MIT license, see the LICENSE file for details.

#include "multi_index.h"

#include <QStringLiteral>

namespace Acoustid {


MultiIndex::MultiIndex(const QSharedPointer<Directory> &dir) : m_dir(dir) {}

void MultiIndex::close() {
    QMutexLocker locker(&m_mutex);
    for (auto &index : m_indexes) {
        index->close();
    }
    m_indexes.clear();
}

QThreadPool *MultiIndex::threadPool() const { return m_threadPool; }

void MultiIndex::setThreadPool(QThreadPool *threadPool) {
    for (auto &index : m_indexes) {
        index->setThreadPool(threadPool);
    }
    m_threadPool = threadPool;
}

bool MultiIndex::indexExists(const QString &name) {
    QMutexLocker locker(&m_mutex);
    if (m_indexes.contains(name)) {
        return true;
    }
    return false;
}

QSharedPointer<Index> MultiIndex::getRootIndex(bool create) {
    return getIndex(ROOT_INDEX_NAME, create);
}

QSharedPointer<Index> MultiIndex::getIndex(const QString &name, bool create) {
    QMutexLocker locker(&m_mutex);
    auto index = m_indexes.value(name);
    if (index) {
        return index;
    }
    if (name == ROOT_INDEX_NAME) {
        index = QSharedPointer<Index>::create(m_dir, create);
        m_indexes[name] = index;
        return index;
    }
    if (create) {
        throw NotImplemented("Index creation is not supported");
    }
    throw IndexNotFoundException("Index does not exist");
}

void MultiIndex::createIndex(const QString &name) {
    getIndex(name, true);
}

void MultiIndex::deleteIndex(const QString &name) {
    throw NotImplemented("Index deletion is not supported");
}

}  // namespace Acoustid
