//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Generated/Forward.h>
#include <obj/Ref.h>
#include <obj/NonCopy.h>
#include <obj/Unique.h>
#include <obj/Type.h>
#include <obj/Util/Global.h>

#include <functional>
#include <vector>

namespace mud
{
	class _refl_ MUD_OBJ_EXPORT Indexer
	{
	public:
		Indexer(Type& type) : m_type(type), m_objects(1, Ref{ type }), m_count(0), m_next(1) {}

		_attr_ Type& m_type;
		_attr_ std::vector<Ref> m_objects;

		inline Id alloc() { return m_next++; }
		inline void add(uint32_t id, Ref object) { this->resize(id); m_objects[id] = object; ++m_count; }
		inline uint32_t index(uint32_t id, Ref object) { if(id == 0) id = this->alloc(); this->add(id, object); return id; }
		inline uint32_t index(Ref object) { uint32_t id = this->alloc(); this->add(id, object); return id; }
		inline void remove(uint32_t id) { m_objects[id] = { m_type }; --m_count; }

		inline void resize(Id id) { if(id >= m_objects.size()) m_objects.resize(id+1); }

		inline void iterate(const std::function<void(Ref)>& callback) const { for(Ref object : m_objects) if(object.m_value) callback(object); }
		inline bool has(uint32_t id) const { return m_objects[id].m_value != nullptr; }

		inline void clear() { m_objects.clear(); m_count = 0; }

	public:
		size_t m_count;
		size_t m_next;
	};

	class _refl_ MUD_OBJ_EXPORT Index : public Global<Index>, public NonCopy
	{
	public:
		Index() : m_indexers(MUD_MAX_TYPES) {}

		_meth_ Indexer& indexer(Type& type)
		{
			if(!m_indexers[type.m_id])
				m_indexers[type.m_id] = make_unique<Indexer>(type);
			return *m_indexers[type.m_id];
		}

#ifdef MUD_META_GENERATOR
		_attr_ static Index instance;
#endif

		std::vector<unique_ptr<Indexer>> m_indexers;
	};

	inline Indexer& indexer(Type& type) { return Index::me().indexer(type); }
	inline uint32_t index(Type& type, uint32_t id, Ref object) { return Index::me().indexer(type).index(id, object); }
	inline uint32_t index(Type& type, Ref object) { return Index::me().indexer(type).index(object); }
	inline void unindex(Type& type, uint32_t id) { Index::me().indexer(type).remove(id); }

	_func_ inline Ref indexed(Type& type, uint32_t id) { return Index::me().indexer(type).m_objects[id]; }
}
