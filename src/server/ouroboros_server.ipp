namespace ouroboros
{
	template <typename Func>
	bool ouroboros_server::register_callback(const std::string& aGroup, const std::string& aField, Func aCallback)
	{
		
		var_field *named = mStore.get(normalize_group(aGroup), aField);
		if (named)
		{
			std::string key(aGroup+"/"+aField);
			
			if (!mCallbackSubjects.count(key))
			{
				mCallbackSubjects[key] = subject<callback<Func> >();
			}
			
			callback<Func> cb(aGroup, aField, aCallback);
			mCallbackSubjects[key].registerObserver(cb);
		}
		return named;
	}
}

