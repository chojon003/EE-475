package com.example.drinkingbuddyapplication.home;

import android.widget.EditText;

import androidx.lifecycle.LiveData;
import androidx.lifecycle.MutableLiveData;
import androidx.lifecycle.ViewModel;

import com.example.drinkingbuddyapplication.databinding.FragmentDashboardBinding;

public class HomeViewModel extends ViewModel {

    private MutableLiveData<String> mText;
    private FragmentDashboardBinding binding;

    public HomeViewModel(String test) {

        mText = new MutableLiveData<>();
        mText.setValue("Hi! I'm your drinking buddy. You have consumed " + test + "oz of water today, which is 35% of your daily goal. Keep up the good work!");
    }

    public LiveData<String> getText() {
        return mText;
    }
}