package com.example.drinkingbuddyapplication.home;

import android.content.Context;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
import androidx.lifecycle.Observer;
import androidx.lifecycle.ViewModelProvider;

import com.example.drinkingbuddyapplication.databinding.FragmentHomeBinding;

public class HomeFragment extends Fragment {

    private HomeViewModel homeViewModel;
    private FragmentHomeBinding binding;
    private View root;
    private TextView text;
    private TextView text1;

    public View onCreateView(@NonNull LayoutInflater inflater,
                             ViewGroup container, Bundle savedInstanceState) {
        binding = FragmentHomeBinding.inflate(inflater, container, false);
        View root = binding.getRoot();
        text = binding.textHome;
        text1 = binding.waterText;
//        text.setText("Hi! I'm your drinking buddy. You have consumed " + test + "oz of water today, which is 35% of your daily goal. Keep up the good work!");

//        homeViewModel =
//                new ViewModelProvider(this).get(HomeViewModel.class);
//

//
//        final TextView textView = binding.textHome;
//        homeViewModel.getText().observe(getViewLifecycleOwner(), new Observer<String>() {
//            @Override
//            public void onChanged(@Nullable String s) {
//                textView.setText(s);
//            }
//        });

//        //read data
//        String name = pref.getString("Name", "");
//        String age = pref.getString("Age", "");
//        String weight = pref.getString("Weight", "");
//
//        int waterNeeded = Integer.parseInt(weight) *
        return root;
    }

    @Override
    public void onDestroyView() {
        super.onDestroyView();
        binding = null;
    }

    @Override
    public void onResume() {
        super.onResume();
        SharedPreferences pref = getActivity().getPreferences(Context.MODE_PRIVATE);
        int totalAmountWaterDrank = pref. getInt("totalAmountWaterDrank", 0);
        int prevMeasWeight = pref.getInt("prevMeasWeight", 0);
        int isWater = pref.getInt("isWater", 0);
        int batteryPct = pref.getInt("batteryPct", 0);

        String isWaterText = "Water";
        if (isWater == 1) {
            isWaterText = "Water";
        } else {
            isWaterText = "Not Water :(";
        }
        text.setText("Water Drank Today: " + totalAmountWaterDrank + "mL" + "\n" +
                " Liquid: " + isWaterText + "\n" + "You should be drinking " + pref.getInt("userDaily", 0) + "ml of water per day."
        + "\n" + "Battery Level: " + batteryPct + "%");
    }
}