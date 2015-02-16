namespace ouroboros
{
	template <typename Func>
	void ouroboros_server::register_callback(const std::string& aGroup, const std::string& aField, Func aCallback)
	{
		var_field *named = mStore.get(normalize_group(aGroup), aField);
		if (named)
		{
			callback<Func> cb(aGroup, aField, aCallback);
			mFieldCallbacks.push_back(cb);
			named->registerObserver(mFieldCallbacks.back());
		}
	}
}