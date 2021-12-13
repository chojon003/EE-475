package com.example.drinkingbuddyapplication;

import android.Manifest;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothGatt;
import android.bluetooth.BluetoothGattCharacteristic;
import android.bluetooth.BluetoothGattService;
import android.content.Context;
import android.content.DialogInterface;
import android.content.SharedPreferences;
import android.content.pm.PackageManager;
import android.location.LocationManager;
import android.os.Build;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AlertDialog;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;
import androidx.fragment.app.Fragment;

import com.clj.fastble.BleManager;
import com.clj.fastble.callback.BleGattCallback;
import com.clj.fastble.callback.BleReadCallback;
import com.clj.fastble.callback.BleScanCallback;
import com.clj.fastble.data.BleDevice;
import com.clj.fastble.exception.BleException;
import com.example.drinkingbuddyapplication.BleDeviceAdapter;
import com.example.drinkingbuddyapplication.databinding.FragmentDashboardBinding;

import java.util.ArrayList;
import java.util.List;

/**
 * A simple {@link Fragment} subclass.
 * Use the {@link Profile#newInstance} factory method to
 * create an instance of this fragment.
 */
public class Profile extends Fragment {

    private FragmentDashboardBinding binding;
    private EditText nameText;
    private EditText ageText;
    private EditText weightText;
    private Spinner lifeSpinner;
    private Spinner sexSpinner;

    private View root;
    // Bluetooth LE UART instance.  This is defined in BluetoothLeUart.java.
    private BluetoothLeUart uart;

    public Profile() {
        // Required empty public constructor
    }

    /**
     * Use this factory method to create a new instance of
     * this fragment using the provided parameters.
     *
     * @param param1 Parameter 1.
     * @param param2 Parameter 2.
     * @return A new instance of fragment Profile.
     */
    // TODO: Rename and change types and number of parameters
    public static Profile newInstance(String param1, String param2) {
        Profile fragment = new Profile();
        Bundle args = new Bundle();
        fragment.setArguments(args);
        return fragment;
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        root = inflater.inflate(R.layout.fragment_profile, container, false);
        nameText = root.findViewById(R.id.editTextName);
        ageText = root.findViewById(R.id.editTextAge);
        weightText = root.findViewById(R.id.editTextWeight);
        lifeSpinner = (Spinner) root.findViewById(R.id.lifestyle);
        sexSpinner = (Spinner) root.findViewById(R.id.sex);

        // Add functionality to save button
        Button saveButton = root.findViewById(R.id.saveButton);
        saveButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                onSave();
            }
        });

        // Add functionality to calibrate color button
        Button calibrateColorButton = root.findViewById(R.id.calibrateColorButton);
        calibrateColorButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                ((MainActivity) getActivity()).onSend();
            }
        });

        // initialize Lifestyle Spinner
        ArrayAdapter<CharSequence> lifeAdapter = ArrayAdapter.createFromResource(getContext(),
                R.array.lifestyle_array, android.R.layout.simple_spinner_item);
        lifeAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        lifeSpinner.setAdapter(lifeAdapter);

        // initialize sex spinner
        ArrayAdapter<CharSequence> sexAdapter = ArrayAdapter.createFromResource(getContext(),
                R.array.sex_array, android.R.layout.simple_spinner_item);
        sexAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        sexSpinner.setAdapter(sexAdapter);

        // instantiate local variables
        SharedPreferences pref = getActivity().getPreferences(Context.MODE_PRIVATE);

        //read data
        String name = pref.getString("Name", "");
        String age = pref.getString("Age", "");
        String weight = pref.getString("Weight", "0");
        String lifestyle = pref.getString("Lifestyle", "");
        String sex = pref.getString("Sex", "");

        // populate fragment with saved values
        nameText.setText(name);
        ageText.setText(age);
        weightText.setText(weight);
        lifeSpinner.setSelection(lifeAdapter.getPosition(lifestyle));
        sexSpinner.setSelection(sexAdapter.getPosition(sex));

        return root;
    }

    public void onSave() {
        SharedPreferences pref = getActivity().getPreferences(Context.MODE_PRIVATE);
        SharedPreferences.Editor editor = pref.edit();
        editor.putString("Name", nameText.getText().toString());
        editor.putString("Age", ageText.getText().toString());
        editor.putString("Weight", weightText.getText().toString());
        editor.putString("Lifestyle", lifeSpinner.getSelectedItem().toString());
        editor.putString("Sex", sexSpinner.getSelectedItem().toString());
        // formula for daily water based on user
        // should drink 2/3 of water weight
        int userDailyIntake = (Integer.parseInt(weightText.getText().toString())) * 2;
        userDailyIntake = userDailyIntake / 3;
        userDailyIntake = userDailyIntake * 30; // convert to ml
        if(lifeSpinner.getSelectedItem().toString().equals("Average")) {
            userDailyIntake += 354;
        } else if(lifeSpinner.getSelectedItem().equals("Athletic")) {
            userDailyIntake += 708;
        }
        editor.putInt("userDaily", userDailyIntake);
        editor.apply();
    }
}

