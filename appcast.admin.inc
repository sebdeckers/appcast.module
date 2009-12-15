<?php
/**
 * This file is part of the Appcast module for Drupal
 * Copyright (c) 2009 Sebastiaan Deckers, Matthias Vandermaesen
 * License: GNU General Public License version 3 or later
 *
 * @file appcast.admin.inc
 *
 */

/**
 * Display module configuration form.
 */
function appcast_settings() {
  $config = _appcast_loadConfig(array('css', 'name', 'track', 'feed', 'path', 'href', 'mirror'));

  $form = array(
    'feed' => array(
      '#type' => 'fieldset',
      '#title' => t('Appcast feed'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
      'appcast_feed' => array(
      '#type' => 'textfield',
      '#title' => t('Appcast feed URL'),
      '#default_value' => $config['feed'],
      '#size' => 90,
      '#maxlength' => 90,
      '#description' => t('URL of the Atom 1.0 feed containing the appcasts.'),
      '#required' => TRUE
    ),
    'appcast_name' => array(
      '#type' => 'textfield',
      '#title' => t('Application name'),
      '#default_value' => $config['name'],
      '#size' => 30,
      '#maxlength' => 60,
      '#description' => t('Name of the software in the appcast feed.'),
      '#required' => TRUE
    ),
    'appcast_track' => array(
      '#type' => 'select',
      '#title' => t('Application track'),
      '#default_value' => $config['track'],
      '#options' => drupal_map_assoc(array('stable', 'beta', 'development')),
      '#description' => t('Track of the software in the appcast feed.'),
      '#required' => TRUE
    )
    ),
    'button' => array(
      '#type' => 'fieldset',
      '#title' => t('Download Button'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
      'appcast_css' => array(
      '#type' => 'textfield',
      '#title' => t('CSS class of the download link'),
      '#default_value' => $config['css'],
      '#size' => 30,
      '#maxlength' => 60,
      '#description' => t('A class name for the containing A element. Use this to style the button with CSS.')
    ),
    'appcast_href' => array(
      '#type' => 'textfield',
      '#title' => t('Download link target'),
      '#default_value' => $config['href'],
      '#size' => 90,
      '#maxlength' => 90,
      '#description' => t('The download button HREF attrtibute. Typically the download page or the URL of a file. Relative URLs should not start with a slash. Specify &lt;front&gt; for the homepage.')
    )
    ),
    'mirror' => array(
      '#type' => 'fieldset',
      '#title' => t('Enclosure Mirror'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
      'appcast_mirror' => array(
      '#type' => 'checkbox',
      '#title' => t('Mirror the enclosure to the local disk.'),
      '#return_value' => 1,
      '#default_value' => $config['mirror'],
      '#description' => t('Download the appcast enclosure to the local disk so that it can be served from this webserver.')
    ),
    'appcast_path' => array(
      '#type' => 'textfield',
      '#title' => t('Local enclosure mirror path'),
      '#default_value' => $config['path'],
      '#size' => 90,
      '#maxlength' => 90,
      '#description' => t('Local file path (directory and filename) to store the downloaded package. The path is relative to the Drupal root directory so be careful not to overwrite system files. If empty the file will be stored as "@files/appcast/[enclosure_filename]". If ending in a trailing slash ("/") the enclosure filename will be appended.', array('@files' => file_directory_path()))
    )
    )
  );

  return system_settings_form($form);
}

/**
 * Validate the module configuration form.
 */
function appcast_settings_validate ($form, &$form_state) {
  $feedUrl = $form_state['values']['appcast_feed'];
  $appName = $form_state['values']['appcast_name'];
  $appTrack = $form_state['values']['appcast_track'];

  // validate only if these required fields are filled. If they aren't, FAPI default validator will take over
  if (!empty($feedUrl) && !empty($appName) && !empty($appTrack)) {
    $appcast = _appcast_latestEntryFromFeed($feedUrl, $appName, $appTrack);
    if (!$appcast) {
      form_set_error('appcast_feed', t('Invalid appcast feed settings. Cannot find the latest appcast. Check the feed URL, application name and application track.'));
      form_set_error('appcast_name', ' ');
      form_set_error('appcast_track', ' ');
    } else {
      $download = _appcast_updateAppcast($appcast, TRUE, $form_state['values']['appcast_path']);
      if (!$download) {
        form_set_error('appcast_feed', t('Failed to download the latest enclosure. Check the log for more information.'));
        form_set_error('appcast_name', ' ');
        form_set_error('appcast_track', ' ');
      }
    }
  }
}
